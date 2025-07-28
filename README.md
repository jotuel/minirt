Made during summer of 2025 as part of studies at Hive, Helsinki. It is a very primitive raytracer with only few shapes, 24-bit color depth, defined ambient color and single light source. I had some alterioir goals during the project which were: 
1) to use malloc & free instead of usual tricks (memory leaks are not allowed),
2) use the list functions written at the start of studies (which are used in parsing scene file and then processing further)
3) follow data-oriented design to get good performance despite our strict limitations

It turned out fine. Because of the implementation the [openmp](https://github.com/jotuel/minirt/tree/openmp) branch worked out quite nicely. Antialiasing & Monte Carlo Pathtracing are something that could still be experimented with there. As of writing, 27.7.25, only a few non-critical rendering issues are known; normal inside objects and cylinder second t-value make the cap leak light and disappear from view when viewed close enough.

There also is a WIP [wasm](https://github.com/jotuel/minirt/tree/openmp) branch that compiles into wasm and js that runs on Node.js. 
