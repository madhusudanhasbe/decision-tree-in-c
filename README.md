# Implementation of Decision Tree in C language
A decision tree is a flowchart-like tree structure where each internal node denotes the feature, branches denote the rules, and the leaf nodes denote the result of the algorithm. 
This project aims to implement a decision tree to assess scholarship eligibility.
The project introduces a user-friendly decision tree implementation for scholarship eligibility, by developing a customizable decision tree structure, enhancing the flexibility to adapt eligibility criteria to their specific requirements. Additionally, the program facilitates checking of past result analysis and allows processing of it.

Methodology of Implementation
1. Decision Tree Construction:
a) Initialize the decision tree by creating nodes for different conditions (e.g., year, GPA,
coding skills, attendance).
b) Establish the hierarchical relationships between nodes by defining the "yes" and "no"
paths.
2. User Interaction
a) Present a user-friendly interface to collect input from the student.
b) Gather information from the student, including year of study, GPA, coding skills,
attendance, and gender.
3. Decision Making
a) Start the decision process at the root node of the decision tree.
b) Evaluate each condition based on the student's input:
• Check if the student's year of study is within the eligible range.
• Verify if the GPA meets the minimum requirement.
• Assess if the student has coding skills.
• Examine attendance and gender to make the final decision.
c) Follow the appropriate "yes" or "no" path based on the evaluation of each condition
until reaching a final decision node.
4. Determine Eligibility
a) If the decision tree leads to an "eligible" node, conclude that the student is eligible for
a scholarship.
b) If the tree leads to a "not eligible" node, determine that the student is not eligible.
5. Log Results
a) Log the scholarship eligibility results in a log file, including student information and
the outcome of the assessment.
6. User Interaction (Optional)
a) Ask the user if they want to continue checking eligibility for other students.
7. Viewing Past Results (Optional)
a) Provide an option to view past scholarship eligibility results.
b) Allow the user to delete specific entries or all entries from the log file.
8. Settings Menu (Optional)
a) Implement a settings menu for users to adjust minimum GPA, minimum attendance,
and eligible year range.
b) Store and update these settings for future assessments.
9. Project Completion
a) The project concludes after the user decides to exit or when all eligible students have
been assessed.
