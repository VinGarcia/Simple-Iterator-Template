
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
struct iterable_it {
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
  static iterable_it begin(C* ref) { return iterable_it(ref, 1); }
  static iterable_it end(C* ref) { return iterable_it(ref, 0); }

 protected:
  iterable_it(C* ref, int state) : ref(ref) {
    if (state) {
      begin();
    } else {
      end();
    }
  }

 public:
  T& operator*() { return *value; }
  iterable_it& operator++() { next(); return *this; }
  bool operator!=(const iterable_it& other) const {
    return value != other.value;
  }
};
