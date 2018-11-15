### Deriving from ```bstd::test::test```:

Create a class that derives ```bstd::test::unit_test``` (```test_class```).
Write unit tests as methods of the derived class. These methods should match the following signature:

```
const bstd::test::result test_class::test_method() const {
  ...
  Test code here
  Initialize success and reason.
  Maybe read member variables (can't write).
  ...

  // The boolean (success) represents the test's success.
  // The string contains the reason for failure if applicable.
  return bstd::test::result(success, reason);
}
```

Where ```bstd::test::result``` is ```std::pair<bool, std::string>```.

Then, in the derived class' constructur use the ```ADD_TEST(test_method)``` macro for each test method. Other methods can be
called from the constructor to do any necessary setup.
Finally, initialize the derived class and call ```derived.run()``` to execute all tests and write results to standard output.

Note: Alternatively, use the ```BSTD_TEST_MAIN(test_class)``` macro to create a main function which runs the tests in this 
class.

### Initializing ```bstd::test::test``` (```bstd::test::test``` can be replaced by your derived class, however the above 
### pattern is preferred):

```
auto my_test = new bstd::test::test();
my_test->add_test("test_name1", test::test1)->add_test("test_name2", test::test2)
    ->add_test("test_name3", test::test3)->run();
```

Where ```test::testx``` are test methods that follow the signature above.

Note: chaining the ```add_test(...)``` and ```run()``` calls are, of course, not required.
Note: ```add_test(...)``` can be replaced by the ```ADD_TEST(...)``` macro as described below.

#### Preprocessor derectives (macros)

```BSTD_TEST_MAIN(test_class)```
  
   Includes a main function that creates an instance of and runs the tests contained in test_class.
   This must be placed after the definition of test_class.

```ADD_TEST(test_class::test_method)```
  
   Adds test_method to test_class' inherited m_tests vector. When run() is called this test will be executed.
   Call from test_class' constructor.

```ADD_TEST(test_function)```
  
   Same as above, but for non-member function.
