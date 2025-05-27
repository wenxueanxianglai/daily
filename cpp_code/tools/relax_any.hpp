#pragma once
#include <stddef.h>

#include <any>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>


namespace zxp {
namespace util {

class RelaxAny {
   public:
    using TypeId = const void *;
    template <typename T>
    static auto GetTypeId() -> TypeId {
        static int type_id{};
        return &type_id;
    }

   public:
    RelaxAny() = default;

    template <typename T, typename D = std::decay_t<T>, typename = std::enable_if_t<!std::is_same_v<D, RelaxAny>>>
    RelaxAny(T &&value) : storage_(std::make_unique<Holder<D>>(std::forward<T>(value))) {}

    RelaxAny(const RelaxAny &other) : storage_(other.storage_ ? other.storage_->clone() : nullptr) {}

    RelaxAny &operator=(const RelaxAny &other) {
        if (this != &other) {
            storage_ = other.storage_ ? other.storage_->clone() : nullptr;
        }
        return *this;
    }

    RelaxAny(RelaxAny &&other) noexcept = default;
    RelaxAny &operator=(RelaxAny &&other) noexcept = default;

   public:
    template <typename T>
    bool is() const {
        return storage_ && (storage_->type_id() == GetTypeId<T>());
    }

    bool has_value() const { return storage_ != nullptr; }
    void reset() { storage_.reset(); }

    template <typename T>
    const T &get() const {
        auto ptr = dynamic_cast<const Holder<T> *>(storage_.get());
        if (!ptr) throw std::bad_cast();
        return ptr->value;
    }

    template <typename T>
    const T *try_get() const {
        if (is<T>()) {
            auto ptr = dynamic_cast<const Holder<T> *>(storage_.get());
            return ptr ? &ptr->value : nullptr;
        }

        return nullptr;
    }

    template <typename T>
    bool can_convert() const {
        return storage_ && storage_->can_convert(GetTypeId<T>());
    }

    template <typename T>
    T convert() const {
        if (!can_convert<T>()) {
            throw std::bad_cast();
        }
        std::any result = storage_->convert_to(GetTypeId<T>());
        try {
            return std::any_cast<T>(result);
        } catch (const std::bad_any_cast &) {
            throw std::bad_cast();
        }
    }

    template <typename T>
    bool can_construct() const {
        return storage_ && storage_->can_construct(GetTypeId<T>());
    }

    template <typename T, typename... Args>
    T &construct(Args &&...args) {
        auto holder = std::make_unique<Holder<T>>(T(std::forward<Args>(args)...));
        T &ref = holder->value;
        storage_ = std::move(holder);
        return ref;
    }

    template <typename T, typename... Args>
    T &emplace(Args &&...args) {
        return construct<T>(std::forward<Args>(args)...);
    }

   public:
    struct Base {
        virtual ~Base() = default;
        virtual std::unique_ptr<Base> clone() const = 0;
        virtual TypeId type_id() const = 0;
        virtual bool can_convert(TypeId to) const = 0;
        virtual std::any convert_to(TypeId to) const = 0;

        virtual bool can_construct(TypeId to) const = 0;
    };

    template <typename T>
    struct Holder : Base {
        T value;
        template <typename U>
        explicit Holder(U &&v) : value(std::forward<U>(v)) {}

        std::unique_ptr<Base> clone() const override { return std::make_unique<Holder<T>>(value); }
        TypeId type_id() const override { return RelaxAny::GetTypeId<T>(); }

        bool can_convert(TypeId to) const override {
            auto it = convert_map().find(to);
            return it != convert_map().end();
        }

        std::any convert_to(TypeId to) const override {
            auto it = convert_map().find(to);
            if (it == convert_map().end()) throw std::bad_cast();
            return it->second(value);
        }

        bool can_construct(TypeId to) const override { return construct_map().find(to) != construct_map().end(); }

        using ConvertMap = std::unordered_map<TypeId, std::function<std::any(const T &)>>;

        static ConvertMap &convert_map() {
            static ConvertMap map;
            return map;
        }

        using ConstructMap = std::unordered_map<TypeId, std::function<std::any(const T &)>>;
        static ConstructMap &construct_map() {
            static ConstructMap map;
            return map;
        }
    };

    std::unique_ptr<Base> storage_;
};

namespace {
template <typename From, typename To>
void register_conversion() {
    RelaxAny::Holder<From>::convert_map()[RelaxAny::GetTypeId<To>()] = [](const From &from) -> std::any {
        if constexpr (std::is_convertible_v<From, To>) {
            return static_cast<To>(from);
        } else {
            throw std::bad_cast();
        }
    };
}

template <typename From, typename To>
void register_construction() {
    RelaxAny::Holder<From>::construct_map()[RelaxAny::GetTypeId<To>()] = [](const From &from) -> std::any {
        if constexpr (std::is_constructible_v<To, From>) {
            return To(from);
        } else {
            throw std::bad_cast();
        }
    };
}

template <typename Tuple, std::size_t I = 0, std::size_t J = 0>
struct RegisterConversionMapper {
    static void apply() {
        using From = std::tuple_element_t<I, Tuple>;
        using To = std::tuple_element_t<J, Tuple>;
        if constexpr (I != J && std::is_convertible_v<From, To>) {
            register_conversion<From, To>();
        }

        if constexpr (J + 1 < std::tuple_size_v<Tuple>) {
            RegisterConversionMapper<Tuple, I, J + 1>::apply();
        } else if constexpr (I + 1 < std::tuple_size_v<Tuple>) {
            RegisterConversionMapper<Tuple, I + 1, 0>::apply();
        }
    }
};

template <typename Tuple, std::size_t I = 0, std::size_t J = 0>
struct RegisterConstructionMapper {
    static void apply() {
        using From = std::tuple_element_t<I, Tuple>;
        using To = std::tuple_element_t<J, Tuple>;

        if constexpr (I != J && std::is_constructible_v<From, To>) {
            register_construction<From, To>();
        }

        if constexpr (J + 1 < std::tuple_size_v<Tuple>) {
            RegisterConstructionMapper<Tuple, I, J + 1>::apply();
        } else if constexpr (I + 1 < std::tuple_size_v<Tuple>) {
            RegisterConstructionMapper<Tuple, I + 1, 0>::apply();
        }
    }
};
static struct __RelaxAnyInitializer {
    __RelaxAnyInitializer() {
        using Builtins =
            std::tuple<bool, char, signed char, unsigned char, wchar_t, char16_t, char32_t, short, unsigned short, int,
                       unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double,
                       std::string, std::string_view, const char *, char *>;
        RegisterConversionMapper<Builtins>::apply();
        RegisterConstructionMapper<Builtins>::apply();
    }
} __sdflksdjfasdasdfa__safasdfasdf_;
}  // namespace
}  // namespace util
}  // namespace zxp