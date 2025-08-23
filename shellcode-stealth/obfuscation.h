#pragma once
#pragma region CONFIG
#define CONST_ENCRYPTION 1
#define CONST_ENCRYPT_MODE 0
#pragma endregion CONFIG
#pragma region OBFUSCATION
#define INLINE __forceinline
#define CAST(T, v) static_cast<T>(v)
#define RCAST(T, v) reinterpret_cast<T>(v)
static constexpr int CTime = __TIME__[0] + __TIME__[1] + __TIME__[3] + __TIME__[4] + __TIME__[6] + __TIME__[7];
#define CTimeSeed ((__COUNTER__ + CTime) * 2654435761u)
#define RND(Min, Max) (Min + (CTimeSeed % (Max - Min + 1)))
#ifdef __cplusplus
#define true 1
#define false 0
namespace meta {
    template<class T> struct remove_reference { using type = T; };
    template<class T> struct remove_reference<T&> { using type = T; };
    template<class T> struct remove_reference<T&&> { using type = T; };
    template<class T> struct remove_const { using type = T; };
    template<class T> struct remove_const<const T> { using type = T; };
    template<class T> struct decay {
        using type = typename remove_const<typename remove_reference<T>::type>::type;
    };
    template<class T> using decay_t = typename decay<T>::type;
}
namespace obf {
    template<class T> using clean_type = typename meta::remove_const<typename meta::remove_reference<T>::type>::type;
    template<typename T, T value>
    INLINE constexpr T ensure_constexpr() { return value; }
    template<typename T, int size>
    constexpr size_t getsize(const T(&)[size]) { return size; }
    template<typename T>
    constexpr size_t getsize(T) { return 1; }
    template<typename T, size_t size>
    constexpr static T gettype(const T(&)[size]);
    template<typename T>
    constexpr static T gettype(T);
    template<class T, size_t size, char key>
    class obfuscator {
    public:
        constexpr obfuscator(const T* data) {
            for (int i = 0; i < size; i++)
                m_data[i] = data[i] ^ CAST(T, key + i);
        }
        constexpr obfuscator(const T data) {
            m_data[0] = data ^ key;
        }
        INLINE T* decrypt() {
            if (!decrypted) {
                for (volatile int i = 0; i < size; i++)
                    m_data[i] = m_data[i] ^ CAST(T, key + i);
            }
            decrypted = true;
            return m_data;
        }
        INLINE operator T* () {
            return decrypt();
        }
        INLINE operator T () {
            return decrypt()[0];
        }
        bool decrypted = false;
        T m_data[size]{};
    };
    static void decoy() {}
    static void decoy_1() { decoy(); }
    static void decoy_2() { decoy(); }
    static void decoy_3() { decoy(); }
    static void decoy_4() { decoy(); }
    static void decoy_5() { decoy(); }
    static void decoy_6() { decoy(); }
    static void decoy_7() { decoy(); }
    static void decoy_8() { decoy(); }
    static void decoy_9() { decoy(); }
    static void decoy_10() { decoy(); }
    template<typename T, int N, int real_index, T real_value, int index>
    constexpr T select_func() {
        T funcs[N + 1] = {
            RCAST(T, (char*)RND(1, 10)), RCAST(T, decoy_1), RCAST(T, decoy_2), RCAST(T, decoy_3),
            RCAST(T, (char*)RND(1, 10)), RCAST(T, 0), RCAST(T, (char*)RND(1, 10)),
            RCAST(T, decoy_5), RCAST(T, (char*)RND(1, 10)), RCAST(T, (char*)RND(1, 10)), RCAST(T, real_value)
        };
        if (index == real_index)
            return funcs[N];
        return reinterpret_cast<T>(funcs[index]);
    }

    template<typename T, int N, int real_index, T real_value, int... indices>
    struct FunctionPtrHider {
        static T shuffled_arr[N];
    };

    template<typename T, int N, int real_index, T real_value, int... indices>
    T FunctionPtrHider<T, N, real_index, real_value, indices...>::shuffled_arr[N] = {
        select_func<T, N, real_index, real_value, indices>()...
    };
}
#define OBF_KEY_NORMAL(x, type, size, key) []() {\
    constexpr static auto result = obf::obfuscator<type, size, key>(x);\
    return result; }() 
#define MAKEOBF_NORMAL(x) OBF_KEY_NORMAL(x, obf::clean_type<decltype(obf::gettype(x))>, obf::getsize(x), (char)RND(1, 255))
#if CONST_ENCRYPTION
#if CONST_ENCRYPT_MODE == 0
#define MAKEOBF(x) MAKEOBF_NORMAL(x)
#endif
#define OBF(x) ((meta::decay_t<decltype(x)>) MAKEOBF(x))
#else
#define OBF(x) x
#endif
#define HIDE_PTR_I(ptr, index) obf::FunctionPtrHider<decltype(ptr), 10, index, ptr, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>::shuffled_arr[OBF(index)]
#define HIDE_PTR(ptr) HIDE_PTR_I(ptr, RND(0, 9))
#define CALL(ptr, ...) (HIDE_PTR(ptr)(__VA_ARGS__))
#else
#define OBF(x) x
#define CALL(ptr, ...) ((ptr)(__VA_ARGS__))
#endif
#pragma endregion OBFUSCATION