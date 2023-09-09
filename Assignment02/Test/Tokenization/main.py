statement = "(p1&p2) => p3)"

# Step 1: Tokenization
tokens = statement.replace('(', ' ( ').replace(')', ' ) ').split()

print(tokens)