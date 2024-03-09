#ifndef CONSTRUCT_H
#define CONSTRUCT_H

// construct : 负责对象的构造
// destroy   : 负责对象的析构

#include "../iterator/iterator.h"
#include "../util.h"

namespace tinystl
{

    template <typename T>
    class Construct
    {
    public:
        template <typename Val>
        static void construct(T &val, const Val &arg) // std::addressof(node->m_data), data ===> new ((void *)ptr) T(data);
        {
            // T *ptr = std::addressof(node->m_data);
            // new ((void *)ptr) T(data);
            T *ptr = std::addressof(val); // 获取val的指针
            new ((void *)ptr) T(arg);
        }

        static void destroy(T &val)
        {
            T *ptr = std::addressof(val);

            if (ptr)
            {
                ptr->~T();
            }
        }
    };

    /**
     * @brief 构造Ty类型对象，ptr指向该对象，
     *
     * @tparam Ty
     * @param ptr
     */
    template <class Ty>
    void construct(Ty *ptr)
    {
        new ((void *)ptr) Ty();
    }

    /**
     * @brief 构造Ty类型对象，ptr指向该对象，带初始值
     *
     * @tparam Ty1
     * @tparam Ty2
     * @param ptr
     * @param value
     */
    template <class Ty1, class Ty2>
    void construct(Ty1 *ptr, const Ty2 &value)
    {
        new ((void *)ptr) Ty1(value);
    }

    /**
     * @brief 构造Ty类型对象，ptr指向该对象，右值
     *
     * @tparam Ty
     * @tparam Args
     * @param ptr
     * @param args
     */
    template <class Ty, class... Args>
    void construct(Ty *ptr, Args &&...args)
    {
        new ((void *)ptr) Ty(tinystl::forward<Args>(args)...);
    }

    // destroy 将对象析构

    template <class Ty>
    void destroy_one(Ty *, std::true_type) {}

    /**
     * @brief 析构
     *
     * @tparam Ty
     * @param pointer
     */
    template <class Ty>
    void destroy_one(Ty *pointer, std::false_type)
    {
        if (pointer != nullptr)
        {
            pointer->~Ty();
        }
    }

    // template <class ForwardIter>
    // void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

    // template <class ForwardIter>
    // void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
    // {
    //     for (; first != last; ++first)
    //         destroy(&*first);
    // }

    template <class Ty>
    void destroy(Ty *pointer)
    {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    // template <class ForwardIter>
    // void destroy(ForwardIter first, ForwardIter last)
    // {
    //     destroy_cat(first, last, std::is_trivially_destructible<typename Iterator_Traits<ForwardIter>::value_type>{});
    // }

} // namespace tinystl

#endif