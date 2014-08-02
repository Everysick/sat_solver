sat_solver
==========

CRuby library


```ruby
require 'SATSolver'

true_case = SatSolver.new.solve(3, [[1, -2], [2, 3], [-3, -1]])

puts true_case

#return
# -> [true, true, false]
#

false_case = SatSolver.new.solve(2, [[1, 2], [1, -2], [-1, 2], [-1, -2]])

puts false_case

#return
# -> false
#

#if your input is mistake
#return 
# -> nil
```
