#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <atomic>   // std::atomic
#include <utility>  // std::swap

class share_count {
public:
    share_count() noexcept
    :count_(1){

    }
    void add_count() noexcept{
        count_.fetch_add(1, std::memory_order_relased);
    }

    long reduce_count() noexcept{
        --count_;
    }

    long get_count() const noexcept{
        return count_;
    }

private:
    std::atomic_long  count_;
};


template <typename T>
class smart_ptr {
    //互相访问私有成员变量
    template <typename U>
    friend class smart_ptr;
public:
    explict smart_ptr(T* ptr = nullptr)
    :ptr_(ptr) {
        //生成新的计数对象
        if (ptr) {
            share_count_ = new share_count();
        }
    }

    ~smart() {
        //计数已经减为 0
        if (ptr_ && !share_count_->reduce_count()) {
            delete ptr_;
            delete share_count_;
        }
    }

    //方便赋值，实现swap函数
    void swap(smart_ptr &rhs)  noexcept {
        using std::swap;
        //转换对象和计数对象
        swap(ptr_, rhs.ptr_);
        swap(share_count_, rhs.share_count_);
    }

    //拷贝构造函数
    template <typename U>
    smart_ptr(const smart_ptr<U>& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            //指针非空引用计数加1
            other.share_count_->add_count();

            //复制共享计数的指针
            share_count_= other.share_count_;
        }
    }

    //移动构造函数
    template <typename U>
    smart_ptr(const smart_ptr<U>&& other) {
        ptr_ = other.ptr_;

        if (ptr_) {
            //引用计数保持不变
            share_count_  = other.share_count_;

            //不再指向该共享对象
            other.ptr_ = nullptr;
        }
    }

    //返回引用计数的值
    long use_count() {

        if (ptr_) {
            return share_count_->get_count();
        }else {
            return 0;
        }
    }

    //对智能指针内部的指针对象赋值时，使用一个现有的智能指针的共享计数
    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) {
        ptr_ = ptr;
        if (ptr_) {
            other.ptr_ = ptr;
            other.share_count_->add_count();
            share_count_ = other.share_count_;
        }
    }

    //获取指针对象
    T* get() const noexcept {
        return ptr_;
    }

    //相应的指针操作 操作符重载
    smart_ptr& operator=(smart_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    T& operator*() const noexcept {
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    operator bool() const noexcept {
        return ptr_;
    }

private:
    T* ptr_;
    share_count* share_count_;
};

//全局的swap
template <typename T>
void swap(smart_ptr& lhs, smart_ptr& rhs){
    lhs.swap(rhs);
}

//实现动态，静态转换需要的函数
template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept {
     T* ptr = dynamic_cast<T*>(other->get());
     return smart_ptr<T>(other, ptr);
}


template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) noexcept {
    T* ptr = static_cast<T*> (other->get());
    return static_cast<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) noexcept {
    T* ptr = reinterpret_cast<T*> (other->get());
    return reinterpret_cast<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) noexcept {
    T* ptr = const_cast<T*> (other->get());
    return const_cast<T>(other, ptr);
}

#endif