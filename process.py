import tskit

ts = tskit.load("no_states.trees")
print(ts.diversity())
print([i for i in ts.haplotypes()])
