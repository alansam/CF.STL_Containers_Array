//
//  arrays.cpp
//  CF.STL_Containers_Array
//
//  Created by Alan Sampson on 3/22/21.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/container
//  @see: https://en.cppreference.com/w/cpp/container/array
//

#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <span>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <array>

using namespace std::literals::string_literals;

//  MARK: - Definitions

//  MARK: - Local Constants.
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_array(int argc, const char * argv[]) -> decltype(argc);

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Containers_Array\n";
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_array(argc, argv);

  return 0;
}

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  MARK: namespace carswp
namespace carswp {

template<class Os, class V> Os & operator<<(Os & os, const V & va) {
  os << "{"s;
  for (auto i_ : va) {
    os << ' ' << i_;
  }
  return os << " } "s;
}
} /* namespace carswp */

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
auto C_array(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array"s << '\n';
  {
    // construction uses aggregate initialization
    std::array<int, 3> a1{ { 1, 2, 3, }, }; // double-braces required in C++11 prior to
                                            // the CWG 1270 revision (not needed in C++11
                                            // after the revision and in C++14 and beyond)
 
    std::array<int, 3> a2 = { 1, 2, 3, };   // double braces never required after =
 
    std::array<std::string, 2> a3 = { std::string("a"s), "b"s };
 
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(),
                      std::ostream_iterator<int>(std::cout, " "));
 
    std::cout << '\n';
 
    // ranged for loop is supported
    for(const auto& s: a3)
        std::cout << s << ' ';
 
    // deduction guide for array creation (since C++17)
    [[maybe_unused]]
    std::array a4 { 3.0, 1.0, 4.0, };  // -> std::array<double, 3>

    std::cout << '\n';
  }

  /// Element access
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - at"s << '\n';
  {
    std::array<int,6> data = { 1, 2, 4, 5, 5, 6, };

    // Set element 1
    data.at(1) = 88;

    // Read element 2
    std::cout << "Element at index 2 has value "s << data.at(2) << '\n';

    std::cout << "data size = "s << data.size() << '\n';

    try {
      // Set element 6
      data.at(6) = 666;
    }
    catch (std::out_of_range const & exc) {
      std::cout << exc.what() << '\n';
    }

    // Print final values
    std::cout << "data:"s;
    for (int elem : data) {
      std::cout << " "s << elem;
    }
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - operator[]"s << '\n';
  {
    std::array<int,4> numbers { 2, 4, 6, 8, };

    std::cout << "Second element: "s << numbers[1] << '\n';

    numbers[0] = 5;

    std::cout << "All numbers:"s;
    for (auto ix : numbers) {
      std::cout << ' ' << ix;
    }
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - front, back, data"s << '\n';
  {
    std::cout << "front"s << '\n';
    {
      std::array<char, 6> letters {'o', 'm', 'g', 'w', 't', 'f'};

      if (!letters.empty()) {
        std::cout << "The first character is '"s << letters.front() << "'.\n"s;
      }

      std::cout << '\n';
    }

    std::cout << "back"s << '\n';
    {
      std::array<char, 6> letters {'a', 'b', 'c', 'd', 'e', 'f'};

      if (!letters.empty()) {
        std::cout << "The last character is '" << letters.back() << "'.\n";
      }

      std::cout << '\n';
    }

    std::cout << "data"s << '\n';
    {
      auto pointer_func = [](const int * p_i, std::size_t size)
      {
          std::cout << "data = ";
          for (std::size_t i_ = 0; i_ < size; ++i_)
            std::cout << p_i[i_] << ' ';
          std::cout << '\n';
      };
       
      auto span_func = [](std::span<const int> data) // since C++20
      {
          std::cout << "data = ";
          for (const int el : data)
            std::cout << el << ' ';
          std::cout << '\n';
      };

      std::array<int,4> container { 1, 2, 3, 4, };

      // Prefer container.data() over &container[0]
      pointer_func(container.data(), container.size());

      // std::span (C++20) is a safer alternative to separated pointer/size.
      span_func({container.data(), container.size()});

      std::cout << '\n';
    }

    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - begin, back, cbegin, cend"s << '\n';
  {
    std::cout << "begin, end"s << '\n';
    {
      std::cout << std::boolalpha;

      std::array<int, 0> empty;
      std::cout << "1) "s
                << (empty.begin() == empty.end()) << ' '     // true
                << (empty.cbegin() == empty.cend()) << '\n'; // true
      // *(empty.begin()) = 42; // => undefined behaviour at run-time


      std::array<int, 4> numbers{5, 2, 3, 4};
      std::cout << "2) "s
                << (numbers.begin() == numbers.end()) << ' '    // false
                << (numbers.cbegin() == numbers.cend()) << '\n' // false
                << "3) "s
                << *(numbers.begin()) << ' '    // 5
                << *(numbers.cbegin()) << '\n'; // 5

      *numbers.begin() = 1;
      std::cout << "4) "s << *(numbers.begin()) << '\n'; // 1
      // *(numbers.cbegin()) = 42; // compile-time error:
                                   // read-only variable is not assignable

      // print out all elements
      std::cout << "5) "s;
      std::for_each(numbers.cbegin(), numbers.cend(), [](int x) {
        std::cout << x << ' ';
      });
      std::cout << '\n';

      std::array constexpr constants{ 'A', 'B', 'C', };
      static_assert(constants.begin() != constants.end());   // OK
      static_assert(constants.cbegin() != constants.cend()); // OK
      static_assert(*constants.begin() == 'A');              // OK
      static_assert(*constants.cbegin() == 'A');             // OK
      // *constants.begin() = 'Z'; // compile-time error:
                                   // read-only variable is not assignable

      std::cout << '\n';
    }

    std::cout << "cbegin, cend"s << '\n';
    {
      /// UTF-16: U+2581, U+u2582, U+2583, U+2584, U+2585, U+2586, U+2587, U+2588
      /// UTF-8 : 0xE2,0x96,0x81 : 0xE2,0x96,0x82 : 0xE2,0x96,0x83 : 0xE2,0x96,0x84
      ///       0xE2,0x96,0x85 : 0xE2,0x96,0x86 : 0xE2,0x96,0x87 : 0xE2,0x96,0x88
#define UTF16_
#if (defined(UTF8_))
      [[maybe_unused]]
      std::array<std::string_view, 8> constexpr data = {
        "\xE2\x96\x81", "\xE2\x96\x82", "\xE2\x96\x83", "\xE2\x96\x84",
        "\xE2\x96\x85", "\xE2\x96\x86", "\xE2\x96\x87", "\xE2\x96\x88",
      };
#elif (defined(UTF16_))
      [[maybe_unused]]
      std::array<std::string_view, 8> constexpr data = {
        "\u2581", "\u2582", "\u2583", "\u2584", "\u2585", "\u2586", "\u2587", "\u2588",
      };
#else
      [[maybe_unused]]
      std::array<std::string_view, 8> constexpr data = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█",
      };
#endif  /* (!defined(UTF8) && !defined(UTF16)) */

      std::array<std::string, std::size(data)> arr;

      std::copy(data.cbegin(), data.cend(), arr.begin());
      //             ^              ^           ^

      auto print = [](const std::string_view str) { std::cout << str << ' '; };

      print("Print 'arr' in direct order using [cbegin, cend):     "s);
      std::for_each(arr.cbegin(), arr.cend(), print);
      //                ^             ^
      std::cout << "\n\n"s;

      print("Print 'arr' in reverse order using [crbegin, crend):  "s);
      std::for_each(arr.crbegin(), arr.crend(), print);
      //                ^^             ^^
      std::cout << "\n"s;

      std::cout << '\n';
    }

    std::cout << "cbegin, crend"s << '\n';
    {
      std::array<int, 11> ai { 1, 11, 11, 35, 0, 12, 79, 76, 76, 69, 40, };

      // print elements of array in reverse order using const_reverse_iterator`s
      std::for_each(ai.crbegin(), ai.crend(), [](int e){ std::cout << e << ' '; });
      //               ^^            ^^
      std::cout << '\n';

      // modify each element of array using non-const reverse_iterator`s
      std::for_each(ai.rbegin(), ai.rend(), [](int & el){ el += 32; });
      //               ^            ^              ^

      // print elements as chars in reverse order using const_reverse_iterator`s
      std::for_each(ai.crbegin(), ai.crend(), [](char el){ std::cout << el; });
      //               ^^            ^^          ^^^^
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - empty"s << '\n';
  {
    std::array<int, 4> numbers { 3, 1, 4, 1, };
    std::array<int, 0> no_numbers;

    std::cout << std::boolalpha;
    std::cout << "numbers.empty(): "s << numbers.empty() << '\n';
    std::cout << "no_numbers.empty(): "s << no_numbers.empty() << '\n';

    std::cout << '\n';
  }
  std::cout << std::endl; //  make sure cout is flushed.

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - empty"s << '\n';
  {
    std::array<int, 4> nums { 1, 3, 5, 7, };

    std::cout << "nums contains "s << nums.size() << " elements.\n"s;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - max_size"s << '\n';
  {
    std::array<char, 10> sa;

    std::cout << "Maximum size of the 'array' is "s << sa.max_size() << "\n"s;

    std::cout << '\n';
  }

  /// Operations
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - fill"s << '\n';
  {
    constexpr int xy = 4;

    using Cell = std::array<unsigned char, 8>;

    std::array<Cell, xy * xy> board;

    //  UTF-16: U+2584 - U+2580, UTF-8: 0xE2, 0x96, 0x84 - 0xE2, 0x96, 0x80
#if (defined(UTF8_))
    board.fill({ {
      '\xE2', '\x96', '\x84',
      '\xE2', '\x96', '\x80',
      '\x00', '\x00',                         // "▄▀";
      //  "\xE2\x96\x84", "\xE2\x96\x80"
    } });                                     // "▄▀";
#elif (defined(UTF16_))
    board.fill({ "\u2584\u2580" });            // "▄▀";
#else
    board.fill({ { 0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0, } });  // "▄▀";
#endif

    std::for_each(board.cbegin(), board.cend(), [xy, On = 1](const auto & cb) mutable {
      std::cout << cb.data() << ((On++ % xy) ? ""s : "\n"s);
    });

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - swap"s << '\n';
  {
    using namespace carswp;

    std::array<int, 3> a1{ 1, 2, 3, }, a2{ 4, 5, 6, };
 
    auto it1 = a1.begin();
    auto it2 = a2.begin();
    int& ref1 = a1[1];
    int& ref2 = a2[1];
 
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
 
    // Note that after swap iterators and references stay associated with their original
    // array, e.g. `it1` still points to element a1[0], `ref1` still refers to a1[1].

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - std::operator==, rtc."s << '\n';
  {
    std::array<int, 3> alice{1, 2, 3};
    std::array<int, 3> bob{7, 8, 9};
    std::array<int, 3> eve{1, 2, 3};

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns "s << (alice == bob) << '\n';
    std::cout << "alice != bob returns "s << (alice != bob) << '\n';
    std::cout << "alice <  bob returns "s << (alice < bob) << '\n';
    std::cout << "alice <= bob returns "s << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns "s << (alice > bob) << '\n';
    std::cout << "alice >= bob returns "s << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns "s << (alice == eve) << '\n';
    std::cout << "alice != eve returns "s << (alice != eve) << '\n';
    std::cout << "alice <  eve returns "s << (alice < eve) << '\n';
    std::cout << "alice <= eve returns "s << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns "s << (alice > eve) << '\n';
    std::cout << "alice >= eve returns "s << (alice >= eve) << '\n';

#if (__cplusplus > 201707L)
    //`TODO:  add spaceship operator tests
    auto eq = std::is_eq(alice <=> eve);
    auto nq = std::is_neq(alice <=> eve);
    auto lt = std::is_lt(alice <=> eve);
    auto le = std::is_lteq(alice <=> eve);
    auto gt = std::is_gt(alice <=> eve);
    auto re = std::is_gteq(alice <=> eve);
#endif  /* (__cplusplus > 201707L) */


    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - std::get"s << '\n';
  {
    std::array<int, 3> arr;

    // set values:
    std::get<0>(arr) = 1;
    std::get<1>(arr) = 2;
    std::get<2>(arr) = 3;

    // get values:
    std::cout << "("s  << std::get<0>(arr)
              << ", "s << std::get<1>(arr)
              << ", "s << std::get<2>(arr)
              << ")\n"s;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - std::swap"s << '\n';
  {
    std::array<int, 3> alice { 1, 2, 3, };
    std::array<int, 3> bob   { 7, 8, 9, };

    auto print = [](const int & nr) { std::cout << ' ' << nr; };

    // Print state before swap
    std::cout << "alice:"s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s "bob  :"s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << "-- SWAP\n"s;
    std::swap(alice, bob);

    // Print state after swap
    std::cout << "alice:"s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s "bob  :"s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << '\n';
  }

#if (__cplusplus > 201707L)
  //`TODO:  add C++20 feature tests
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::array - std::to_array"s << '\n';
  {
    // copies a string literal
    auto a1 = std::to_array("foo"s);
    static_assert(a1.size() == 4);

    // deduces both element type and length
    auto a2 = std::to_array({ 0, 2, 1, 3 });
    static_assert(std::is_same_v<decltype(a2), std::array<int, 4>>);

    // deduces length with element type specified
    // implicit conversion happens
    auto a3 = std::to_array<long>({ 0, 1, 3 });
    static_assert(std::is_same_v<decltype(a3), std::array<long, 3>>);

    auto a4 = std::to_array<std::pair<int, float>>(
        { { 3, .0f }, { 4, .1f }, { 4, .1e23f } });
    static_assert(a4.size() == 3);

    // creates a non-copyable std::array
    auto a5 = std::to_array({ std::make_unique<int>(3) });
    static_assert(a5.size() == 1);

    // error: copying multidimensional arrays is not supported
    // char s[2][6] = { "nice", "thing" };
    // auto a6 = std::to_array(s);

    std::cout << '\n';
  }
#endif  /* (__cplusplus > 201707L) */

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}
