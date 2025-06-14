# PicoJSON - a C++ JSON parser / serializer

Copyright &copy; 2009-2010 Cybozu Labs, Inc.
Copyright &copy; 2011-2015 Kazuho Oku

Licensed under [2-clause BSD license](http://opensource.org/licenses/BSD-2-Clause)

## Version

1.3.1-dev [![Build Status](https://travis-ci.org/kazuho/picojson.svg?branch=master)](https://travis-ci.org/kazuho/picojson)

## Introduction

PicoJSON is a tiny JSON parser / serializer for C++ with following properties:

- header-file only
- no external dependencies (only uses standard C++ libraries)
- STL-frendly (arrays are represented by using std::vector, objects are std::map)
- provides both pull interface and streaming (event-based) interface

## Reading JSON using the pull interface

There are several ways to use the pull (DOM-like) interface of picojson.

The easiest way is to use the two-argument `parse` function.

```
std::string json = "[ \"hello JSON\" ]";
picojson::value v;
std::string err = picojson::parse(v, json);
if (! err.empty()) {
  std:cerr << err << std::endl;
}
```

Four-argument `parse` function accepts a pair of iterators, and returns the end position of the input.

```
const char* json = "{\"a\":1}";
picojson::value v;
std::string err;
const char* json_end = picojson::parse(v, json, json + strlen(json), &err);
if (! err.empty()) {
  std::cerr << err << std::endl;
}
```

```
std::istream_iterator input(std::cin);
picojson::value v;
std::string err;
input = picojson::parse(v, input, std::istream_iterator(), &err);
if (! err.empty()) {
  std::cerr << err << std::endl;
}
```

It is also possible to use the `>>` operator to parse the input, however this interface is not thread-safe.

```
picosjon::value v;
std::cin >> v;
std::string err = picojson::get_last_error();
```

## Accessing the values

Values of a JSON object is represented as instances of picojson::value class.

<pre>
namespace picojson {

  class value {
    ...

  public:

    typedef std::vector&lt;value&gt; array;
    typedef std::map&lt;std::string, value&gt; object;

    value();                               // create a null object
    explicit value(bool b);                // create a boolean object
    explicit value(double n);              // create a number object
    explicit value(const std::string& s);  // create a string object
    explicit value(const array& a);        // create an array object
    explicit value(const object& o);       // create an "object"

    bool is&lt;picojson::null&gt;() const;       // check if the object is "null"

    bool is&lt;bool&gt;() const;                 // check if the object is a boolean
    const bool& get&lt;bool&gt;() const;         // const accessor (usable only if the object is a boolean)
    bool& get&lt;bool&gt;();                     // non-const accessor (usable only if the object is a boolean)

    bool is&lt;double&gt;() const;               // check if the object is a number
    const double& get&lt;double&gt;() const;     // const accessor (usable only if the object is a number)
    double& get&lt;double&gt;();                 // non-const accessor (usable only if the object is a number)

    bool is&lt;std::string&gt;() const;          // check if the object is a string
    const std::string& get&lt;std::string&gt;() const;
                                           // const accessor (usable only if the object is a string)
    std::string& get&lt;std::string&gt;();       // non-const accessor (usable only if the object is a string)

    bool is&lt;array&gt;() const;                // check if the object is an array
    const array& get&lt;array&gt;() const;       // const accessor (usable only if the object is an array)
    array& get&lt;array&gt;();                   // non-const accessor (usable only if the object is an array)

    bool is&lt;object&gt;() const;               // check if the object is an "object"
    const object& get&lt;object&gt;() const;     // const accessor (usable only if the object is an object)
    object& get&lt;object&gt;();                 // non-const accessor (usable only if the object is an array)

    bool evaluate_as_boolean() const;      // evaluates the object as a boolean

    std::string serialize() const;         // returns the object in JSON representation
    template<typename Iter> void serialize(Iter os) const;
                                           // serializes the object in JSON representation through an output iterator

    std::string to_str() const;            // returns the object in string (for casual use)

  };

}
</pre>

The code below parses a JSON string and prints the contents of the object.

<pre>
picojson::value v;

// parse the input
std::cin &gt;&gt; v;
std::string err = picojson::get_last_error();
if (! err.empty()) {
  std::cerr &lt;&lt; err &lt;&lt; std::endl;
  exit(1);
}

// check if the type of the value is "object"
if (! v.is&lt;picojson::object&gt;()) {
  std::cerr &lt;&lt; "JSON is not an object" &lt;&lt; std::endl;
  exit(2);
}

// obtain a const reference to the map, and print the contents
const picojson::value::object& obj = v.get&lt;picojson::object&gt;();
for (picojson::value::object::const_iterator i = obj.begin();
     i != obj.end();
     ++i) {
  std::cout &lt;&lt; i-&gt;first &lt;&lt; ': ' &lt;&lt; i-&gt;second.to_str() &lt;&lt; std::endl;
}
</pre>

Please note that the type check is mandatory; do not forget to check the type of the object by calling is&lt;type&gt;() before accessing the value by calling get&lt;type&gt;().

## Reading JSON using the streaming (event-driven) interface

Please refer to the implementation of picojson::default_parse_context and picojson::null_parse_context. There is also an example (examples/streaming.cc) .

## Serializing to JSON

Instances of the picojson::value class can be serialized in three ways, to ostream, to std::string, or to an output iterator.

<pre>
picojson::value v;
...
std::cout &lt;&lt; v;
</pre>

<pre>
picojson::value v;
...
std::string json = v.serialize();
</pre>

<pre>
picojson::value v;
...
v.serialize(std::ostream_iterator&lt;char&gt;(std::cout));
</pre>

## Experimental support for int64_t

Experimental suport for int64_t becomes available if the code is compiled with preprocessor macro `PICOJSON_USE_INT64`.

Turning on the feature will cause following changes to picojson:

- new constructor `picojson::value(int64_t)` is defined
- `is<int64_t>()` and `get<int64_t>()` become available
- numerics in JSON within the bounds of int64_t and not using `.` nor `e`/`E` are considered as int64 type
- the values are also avaliable as `double`s as well (i.e. all values which are `.is<int64_t>() == true` are also `.is<double>() == true`)
- int64 values are converted to double once `get<double>()` is called

Enabling the feature should not cause compatibility problem with code that do not use the feature.

## Further reading

Examples can be found in the <i>examples</i> directory, and on the [Wiki](https://github.com/kazuho/picojson/wiki). Please add your favorite examples to the Wiki.
