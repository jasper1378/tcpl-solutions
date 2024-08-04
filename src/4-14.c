#define swap(t_, x_, y_)                                                       \
  {                                                                            \
    t_ z_;                                                                     \
    z_ = x_;                                                                   \
    x_ = y_;                                                                   \
    y_ = z_;                                                                   \
  }
