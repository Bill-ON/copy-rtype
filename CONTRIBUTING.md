## Contributing to South Invaders

Hello contributors! Welcome to South Invaders! 

Do you enjoy South Invaders and want to contribute? Nice! You can help with the following points:

- `C++ programming` - Can you write/review/test/improve the code? 
- `Documentation/Tutorials/Example` - Can you write some tutorial/example?
- `Porting to other platforms` - Can you port/adapt/compile South Invaders on other systems?
- `Testing` - Can you find some bugs in South Invaders?

This document contains a set of guidelines to contribute to the project. These are mostly guidelines, not rules. 
Use your best judgement, and feel free to propose changes to this document in a pull request.

### Opening new Issues

To open new issue for South Invaders (Report a security vulnerability, Question, Feature Request, Bug Report...), just try to follow these rules:

 - Make sure the issue has not already been reported before by searching on GitHub under Issues.
 - If you're unable to find an open issue addressing the problem, open a new one. Be sure to include a 
 title and clear description, as much relevant information as possible, and a code sample demonstrating the unexpected behavior.
 - If applies, attach some screenshot of the issue and a .zip file with the code sample and required resources.
 - On issue description, add a brackets tag about the South Invaders module that relates to this issue. 
 If don't know which module, just report the issue, we will review it.
 - You can check other issues to see how it's done!

### Sending a Pull-Request

 - Make sure the PR description clearly describes the problem and solution. Include the relevant issue number if applicable.
 - Don't send big pull requests (lots of changelists), they are difficult to review. It's better to send small pull requests, one at a time.
 - Verify that changes don't break the build (at least on Windows). As many platforms where you can test it, the better, but don't worry
 if you cannot test all the platforms.

### How to Commit

To ensure your commits are readable by everyone, you need to follow this example:
`[FIX] : flavor text grammar`

- use Brackets to encapsulate the key word
- use one of the following words to best summarize your commit:
    - ADD -> add new functionnalities to South Invaders
    - UPDATE -> change an already existing feature
    - CLEAN -> make your code more readable or change parts to comply with our [guideline](CONVENTIONS.md)
    - FIX -> repair a defective part of our game
    - DELETE -> suppress nefarious code
    - MERGE -> fuse Github branches

- after closing your brackets, use a *space*, *colons*, and another *space* -> " : "
- give a brief summary of what you've done
- if you wish to give additional information about your actions, you may comment your commit (make sure it's syntax and grammar are perfect, we may refuse illegible commits)
