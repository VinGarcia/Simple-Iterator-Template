
#define MAKE_ITERABLE(T) \
  typedef ptrdiff_t difference_type;\
  typedef size_t size_type;\
  typedef T value_type;\
  typedef T* pointer;\
  typedef T& reference;

// C - The container type
// T - The content type
// S - The state keeping structure
template <class C, typename T, class S>
struct iterator_tpl {
  // Keeps a reference to the container:
  C* ref;

  // Keeps a reference to the current value:
  T* value;

  S state;

  // Set iterator to next() state:
  // (Set value to 0 if next is end state)
  void next();
  // Initialize `value` to first state:
  void begin();
  // Initialize `value` to end state:
  void end();

 public:
  static iterator_tpl begin(C* ref) { return iterator_tpl(ref, 1); }
  static iterator_tpl end(C* ref) { return iterator_tpl(ref, 0); }

  static iterator_tpl begin(const C* ref) { return iterator_tpl(ref, 1); }
  static iterator_tpl end(const C* ref) { return iterator_tpl(ref, 0); }

 protected:
  iterator_tpl(C* ref, int state) : ref(ref) {
    if (state) {
      begin();
    } else {
      end();
    }
  }

 public:
  T& operator*() { return *value; }
  iterator_tpl& operator++() { next(); return *this; }
  bool operator!=(const iterator_tpl& other) const {
    return value != other.value;
  }
};
