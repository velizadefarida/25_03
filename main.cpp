#include "pe-vector.hpp"
#include <iostream>
#include <cstring>

using   knk::Vector;

bool testConstructAndDestruct(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool testDefaultVectorIsEmpty(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2;
  Vector< int > v(size, 10);
  return v.getSize() == size;
}

bool testPushBackOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.pushBack(7);
  return v.getSize() == size + 1;
}

bool testPushBackOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(7);
  return v.getSize() == 1;
}

bool testPopBackOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.popBack();
  return v.getSize() == size - 1;
}

bool testPopBackOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.popBack();
  return v.getSize() == 0 && v.isEmpty();
}

bool testGetCapacityOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v(5, 10);
  v.pushBack(7);
  return v.getCapacity() == 10;
}

bool testGetCapacityOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.getCapacity() == 0;
}

bool testCopyConstructor(const char ** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  Vector< int > yav = v;
  if (!v.isEmpty() && !yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testElementCheckedAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try {
    int & r = v.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedConstAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int & r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundConstAccess(const char ** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}

bool testMoveConstructor(const char ** pname) {
  *pname = __func__;
  Vector<int> v1{1, 2, 3};
  Vector<int> v2 = std::move(v1);
  return v2.getSize() == 3 && v2[0] == 1 && v2[1] == 2 && v2[2] == 3 &&
         v1.getSize() == 0 && v1.getCapacity() == 0;
}

bool testCopyAssignment(const char ** pname) {
  *pname = __func__;
  Vector<int> v1{1, 2, 3};
  Vector<int> v2;
  v2 = v1;
  if (v1.getSize() != v2.getSize()) return false;
  for (size_t i = 0; i < v1.getSize(); ++i)
    if (v1[i] != v2[i]) return false;
  return true;
}

bool testMoveAssignment(const char ** pname) {
  *pname = __func__;
  Vector<int> v1{4, 5, 6};
  Vector<int> v2;
  v2 = std::move(v1);
  return v2.getSize() == 3 && v2[0] == 4 && v2[1] == 5 && v2[2] == 6 &&
         v1.getSize() == 0 && v1.getCapacity() == 0;
}

bool testSubscriptOperator(const char ** pname) {
  *pname = __func__;
  Vector<int> v{10, 20, 30};
  v[1] = 99;
  const Vector<int>& cv = v;
  return v[0] == 10 && v[1] == 99 && v[2] == 30 && cv[1] == 99;
}

bool testSwap(const char ** pname) {
  *pname = __func__;
  Vector<int> v1{1, 2};
  Vector<int> v2{3, 4, 5};
  v1.swap(v2);
  return v1.getSize() == 3 && v1[0] == 3 && v1[1] == 4 && v1[2] == 5 &&
         v2.getSize() == 2 && v2[0] == 1 && v2[1] == 2;
}

bool testPushFront(const char ** pname) {
  *pname = __func__;
  Vector<int> v{2, 3};
  v.pushFront(1);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertSingle(const char ** pname) {
  *pname = __func__;
  Vector<int> v{1, 3};
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v{1, 5};
  Vector<int> src{2, 3, 4};
  v.insert(1, src, 0, 3);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5;
}

bool testEraseSingle(const char ** pname) {
  *pname = __func__;
  Vector<int> v{1, 2, 3};
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v{1, 2, 3, 4, 5};
  v.erase(1, 4);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

int main() {
  using test_t = bool(*)(const char **);
 bool testPushFront(const char ** pname) {
  *pname = __func__;
  Vector<int> v{2, 3};
  v.pushFront(1);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
} using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of empty vector must be positive" },
    { testPushBackOfNoneEmptyVector, "pushBack must increase size" },
    { testPopBackOfNoneEmptyVector, "popBack must decrease size" },
    { testGetCapacityOfNoneEmptyVector, "Capacity must double when size" },
    { testPushBackOfEmptyVector, "pushBack on empty vector must increase size" },
    { testPopBackOfEmptyVector, "popBack on empty vector must do nothing" },
    { testGetCapacityOfEmptyVector, "Capacity of empty vector must be zero" },
    { testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value" },
    { testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
    { testCopyConstructor, "Copied vector must be equal to original" },
    { testElementCheckedConstAccess, "Same as ElementCheckedAccess, but const" },
    { testElementCheckedOutOfBoundConstAccess, "Same as ElementCheckedOutOfBoundAccess, but const" }
    { testMoveConstructor, "Move constructor transfers ownership" },
    { testCopyAssignment, "Copy assignment must copy all elements" },
    { testMoveAssignment, "Move assignment must transfer ownership" },
    { testSubscriptOperator, "operator[] must allow read/write access" },
    { testSwap, "swap must exchange contents" },
    { testPushFront, "pushFront must insert at beginning" }
    { testInsertSingle, "insert single element at index" },
    { testInsertRange, "insert range from another vector" },
    { testEraseSingle, "erase single element by index" },
    { testEraseRange, "erase range of indices" }
};
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[NOT RUN]" << testName << "\n";
      std::cout << "\t" << "reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "[FAIL] " << testName << "\n";
      std:: cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
