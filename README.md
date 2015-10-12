# LDMud-doc
The end goal of this project is to make the documentation for LDMud (https://github.com/ldmud/ldmud) easier to convert incorporate with Doxygen-based documentation projects.

To be less vague, the path to that destination includes:
* create guidelines and code to define RST/Sphinx idioms which improve the documentation semantics and standardize formatting/quality.
* create a linter capable of enforcing standards that can be reasonably enforced on the documentation
* convert the existing LDMud documentation to this new format
* create/refine code to generate relevant output formats (HTML, plaintext, Doxygen-ready pseudocode & markdown)
* improve the quality of the documentation along the way (i.e., I will already be touching every documentation file and reading almost every word of the documentation several times; I might as well fix/improve/report any issues I see)

## Status
I have completed an initial conversion pass on most of the existing documentation to identify edge cases and issues with the current (tentative) documentation format. The task at hand is ironing out these formatting issues and settling the format. When the format is settled, the primary task will be producing a good specification for this format, and updating the linter scaffold to enforce everything it can. The *hope* is that the linter can be used to guide the final push to bring the documentation into line with the standard. After this is completed, I'll be able to build an extension to generate a Doxygen-ready copy of the docs.
