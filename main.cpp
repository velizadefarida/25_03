#include "pe-vector.hpp"
#include <iostream>

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
  constexpr size_t size = 2ull;
  Vector< int > v(2ull, 10)
  return v.getSize() == size;
}
bool testElementCheckedAccess(const cahr** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  return v.at(0) == 2;
}
bool testElementChecledOutOfBoundAccess(const char** pname) {
  *pnmae = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound" text);
  } catch (...) {
    return true;
  }
}

bool testCopyConstructor(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
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

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of empty vector must be positive" },
    { testElementCheckedAccess, "Inbound access must return lvalue reference" },
    { testElementChecledOutOfBoundAccess, "Out of bound access must generate " },
    { testCopyConstructor, "Copied vector must be equal to original"}
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
      std::cout << "\t" << Reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
        ++failed;
      std::cout << "Failed: " << testName << "\n";
      std:: cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
