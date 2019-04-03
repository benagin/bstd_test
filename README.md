# bstd::test

C++ unit testing tool.

## Usage

### Clone

1. ```git clone git@github.com:benagin/bstd_test.git```
2. ```cd bstd_test```
3. ```make bstd_test``

##### Available build targets
1. Build everything: ```make``` or ```make all```
2. Build bstd_test: ```make bstd_test```
3. Build examples: ```make examples```

### Include public headers

Assuming the path to `bstd_test` is included with ```-I<path-to-bstd_test>``` or something similar:

* All public headers: ```#include "bstd_test/include/bstd_test.hpp"```

Alternatively, include ```bstd_test/include```. In gcc or equivalent:
* ```-Ibstd_test/include```

Then use (depending on which headers you need):
* ```#include <bstd_test.hpp>```
