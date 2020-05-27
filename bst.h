#ifndef CS270_BINARYTREE
#define CS270_BINARYTREE
template<class E>
class BinaryTree {
 public:
  template<class IMPL> class Position {
   public:
    E& operator*();
    IMPL parent();
    IMPL left();
    IMPL right();
    bool isLeaf() const;
    bool isRoot() const;
    bool isValid() const;
  };
  bool isEmpty() { return size() == 0; }
  template<class IMPL> Position<IMPL> getRoot();
  virtual int size() const = 0;
};

#endif // CS270_BINARYTREE
