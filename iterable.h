
#define SETUP_ITERATOR(C, T, S) \
  typedef std::ptrdiff_t difference_type;\
  typedef size_t size_type;\
  typedef T value_type;\
  typedef T* pointer;\
  typedef T& reference;\
  typedef iterator_tpl<C, T, S> iterator;\
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
  void next() { state.next(ref); }
  // Initialize iterator to first state:
  void begin() { state.begin(ref); }
  // Initialize iterator to end state:
  void end() { state.end(ref); }
  // Returns current `value`
  T& get() { return state.get(ref); }

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
