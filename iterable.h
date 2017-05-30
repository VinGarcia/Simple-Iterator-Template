
#define SETUP_ITERATOR(C, T, S) \
  typedef ptrdiff_t difference_type;\
  typedef size_t size_type;\
  typedef T value_type;\
  typedef T* pointer;\
  typedef T& reference;\
  typedef iterator_tpl<test, int, int> iterator;\
  iterator begin() { return iterator::begin(this); }\
  iterator end() { return iterator::end(this); }

// C - The container type
// T - The content type
// S - The state keeping structure
template <class C, typename T, class S>
struct iterator_tpl {
  // Keeps a reference to the container:
  C* ref;

  S state;

  // Set iterator to next() state:
  void next();
  // Initialize iterator to first state:
  void begin();
  // Initialize iterator to end state:
  void end();
  // Returns current `value`
  T& get();

 public:
  static iterator_tpl begin(C* ref) { return iterator_tpl(ref, 1); }
  static iterator_tpl end(C* ref) { return iterator_tpl(ref, 0); }

 protected:
  iterator_tpl(C* ref, int state) : ref(ref) {
    if (state) {
      begin();
    } else {
      end();
    }
  }

 public:
  T& operator*() { return get(); }
  iterator_tpl& operator++() { next(); return *this; }
  bool operator!=(iterator_tpl& other) {
    return ref != other.ref || get() != other.get();
  }
};
