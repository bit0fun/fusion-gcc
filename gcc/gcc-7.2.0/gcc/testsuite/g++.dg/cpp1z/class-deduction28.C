// PR c++/79350
// { dg-options -std=c++1z }

template <class T>
struct A
{
  explicit A(T);
};


A a (42);
A a2 = 42; 			// { dg-error "" }

template <class T>
struct B
{
  B(T*);
};

template <class T>
explicit B(T) -> B<T*>;

B b1 (0);
B b2 = 0;			// { dg-error "" }
