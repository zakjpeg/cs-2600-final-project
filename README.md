
# CSpend

CSpend is a personal finance tool used to track spending across various categories.

### Mission
CSpend's goal is to help users gain control over their personal finance. The CSpend algorithm calculates spending ratios and gives the user actionable advice to build better spending and saving habits.

### Setup
1. In cspend.c update the OP_SYS variable to:
    - 1 if using windows
    - 0 if using unix
2. run "make" command

### More Info
CSpend analyzes and advises using the 50/30/20 rule. This means that no more than 50% of your income should go to needs, no more than 30% to wants, and at least 20% to savings.

Your spending logs are recorded locally, and can be found in "expenses.log". To clear your expense history, simply delete "expenses.log" and run cspend again to create a fresh expense log.