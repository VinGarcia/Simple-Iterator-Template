
namespace iterator_tpl {

// Use this define to declare both:
// - `iterator`
// - `const_iterator`:
// As members of your class
#define SETUP_ITERATORS(C, T, S) \
  _SETUP_MUTABLE_ITERATOR(C, T, S) \
  _SETUP_CONST_ITERATOR(C, T, S)

// Use this define to declare only `iterator`
#define SETUP_CONST_ITERATOR_ONLY(C, T, S) \
  _SETUP_CONST_ITERATOR(C, T, S)

// Use this define to declare only `const_iterator`
#define SETUP_MUTABLE_ITERATOR_ONLY(C, T, S) \
  _SETUP_MUTABLE_ITERATOR(C, T, S)

#define STL_TYPEDEFS(T) \
  typedef std::ptrdiff_t difference_type;\
  typedef size_t size_type;\
  typedef T value_type;\
  typedef T* pointer;\
  typedef const T* const_pointer;\
  typedef T& reference;\
  typedef const T& const_reference;

/* * * * * MUTABLE ITERATOR TEMPLATE: * * * * */

// C - The container type
// T - The content type
// S - The state keeping structure
template <class C, typename T, class S>
struct iterator {
  // Keeps a reference to the container:
  C* ref;

  // User defined struct to describe the iterator state:
  // This struct should provide the 4 functions listed below
  // and an additional `const T& get();` if you plan on using
  // the const_iterator version.
  S state;

  // Set iterator to next() state:
  void next() { state.next(ref); }
  // Initialize iterator to first state:
  void begin() { state.begin(ref); }
  // Initialize iterator to end state:
  void end() { state.end(ref); }
  // Returns current `value`
  T& get() { return state.get(ref); }

 public:
  static iterator begin(C* ref) { return iterator(ref, 1); }
  static iterator end(C* ref) { return iterator(ref, 0); }

 protected:
  iterator(C* ref, int state) : ref(ref) {
    if (state) {
      begin();
    } else {
      end();
    }
  }

 public:
  T& operator*() { return get(); }
  iterator& operator++() { next(); return *this; }
  bool operator!=(iterator& other) {
    return ref != other.ref || get() != other.get();
  }
};

/* * * * * CONST ITERATOR TEMPLATE: * * * * */

// C - The container type
// T - The content type
// S - The state keeping structure
template <class C, typename T, class S>
struct const_iterator {
  // Keeps a reference to the container:
  const C* ref;

  S state;

  // Set iterator to next() state:
  void next() { state.next(ref); }
  // Initialize iterator to first state:
  void begin() { state.begin(ref); }
  // Initialize iterator to end state:
  void end() { state.end(ref); }
  // Returns current `value`
  const T& get() { return state.get(ref); }

 public:
  static const_iterator begin(const C* ref) {
    return const_iterator(ref, 1);
  }
  static const_iterator end(const C* ref) {
    return const_iterator(ref, 0);
  }

 protected:
  const_iterator(const C* ref, int state) : ref(ref) {
    if (state) {
      begin();
    } else {
      end();
    }
  }

 public:
  const T& operator*() { return get(); }
  const_iterator& operator++() { next(); return *this; }
  bool operator!=(const_iterator& other) {
    return ref != other.ref || get() != other.get();
  }
};

// These 2 defines are for internal use of the library,
// prefer to use the ones described on the top of this file.
#define _SETUP_MUTABLE_ITERATOR(C, T, S) \
  typedef iterator_tpl::iterator<C, T, S> iterator;\
  iterator begin() { return iterator::begin(this); }\
  iterator end() { return iterator::end(this); }

#define _SETUP_CONST_ITERATOR(C, T, S) \
  typedef iterator_tpl::const_iterator<C, T, S> const_iterator;\
  const_iterator begin() const { const_iterator::begin(this); }\
  const_iterator end() const { const_iterator::end(this); }

}  // namespace iterator_tpl
