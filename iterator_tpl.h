
namespace iterator_tpl {

// Use this define to declare both:
// - `iterator`
// - `const_iterator`:
// As members of your class
#define SETUP_ITERATORS(C, T, S) \
  SETUP_MUTABLE_ITERATOR(C, T, S) \
  SETUP_CONST_ITERATOR(C, T, S)

// Use this define to declare only `iterator`
#define SETUP_MUTABLE_ITERATOR(C, T, S) \
  typedef iterator_tpl::iterator<C, T, S> iterator;\
  iterator begin() { return iterator::begin(this); }\
  iterator end() { return iterator::end(this); }

// Use this define to declare only `const_iterator`
#define SETUP_CONST_ITERATOR(C, T, S) \
  typedef iterator_tpl::const_iterator<C, T, S> const_iterator;\
  const_iterator begin() const { return const_iterator::begin(this); }\
  const_iterator end() const { return const_iterator::end(this); }

#define STL_TYPEDEFS(T) \
  typedef std::ptrdiff_t difference_type;\
  typedef size_t size_type;\
  typedef T value_type;\
  typedef T* pointer;\
  typedef const T* const_pointer;\
  typedef T& reference;\
  typedef const T& const_reference

// Forward declaration of const_iterator:
template <class C, typename T, class S>
class const_iterator;

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
  // Optional used for const comparisons:
  const T& get() const { return state.get(ref); }
  bool cmp(const S& s) const { return state.cmp(s); }

 public:
  static iterator begin(C* ref) { return iterator(ref, 0); }
  static iterator end(C* ref) { return iterator(ref, 1); }

 protected:
  iterator(C* ref, int initial_state) : ref(ref) {
    switch (initial_state) {
    case 0: begin(); break;
    case 1: end(); break;
    }
  }

 public:
  // Note: Instances build with this constructor should
  // be used only after copy-assigning from other iterator!
  iterator() {}

 public:
  T& operator*() { return get(); }
  T* operator->() { return &get(); }
  iterator& operator++() { next(); return *this; }
  iterator operator++(int) { next(); return *this; }
  bool operator!=(const iterator& other) const {
    return ref != other.ref || cmp(other.state);
  }
  bool operator==(const iterator& other) const {
    return !operator!=(other);
  }

  friend class iterator_tpl::const_iterator<C,T,S>;

  // Comparisons between const and normal iterators:
  bool operator!=(const const_iterator<C,T,S>& other) const {
    return ref != other.ref || cmd(other.state);
  }
  bool operator==(const const_iterator<C,T,S>& other) const {
    return !operator!=(other);
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
  bool cmp(const S& s) const { return state.cmp(s); }

 public:
  static const_iterator begin(const C* ref) {
    return const_iterator(ref, 0);
  }
  static const_iterator end(const C* ref) {
    return const_iterator(ref, 1);
  }

 protected:
  const_iterator(const C* ref, int initial_state) : ref(ref) {
    switch (initial_state) {
    case 0: begin(); break;
    case 1: end(); break;
    }
  }

 public:
  // Note: Instances build with this constructor should
  // be used only after copy-assigning from other iterator!
  const_iterator() {}

  // To make possible copy-construct non-const iterators:
  const_iterator(const iterator<C,T,S>& other) : ref(other.ref) {
    state = other.state;
  }

 public:
  const T& operator*() { return get(); }
  const T* operator->() { return &get(); }
  const_iterator& operator++() { next(); return *this; }
  const_iterator operator++(int) { next(); return *this; }
  bool operator!=(const const_iterator& other) const {
    return ref != other.ref || cmp(other.state);
  }
  bool operator==(const const_iterator& other) const {
    return !operator!=(other);
  }
  const_iterator& operator=(const iterator<C,T,S>& other) {
    ref = other.ref;
    state = other.state;
    return *this;
  }

  friend class iterator_tpl::iterator<C,T,S>;

  // Comparisons between const and normal iterators:
  bool operator!=(const iterator<C,T,S>& other) const {
    return ref != other.ref || cmp(other.state);
  }
  bool operator==(const iterator<C,T,S>& other) const {
    return !operator!=(other);
  }
};

}  // namespace iterator_tpl
