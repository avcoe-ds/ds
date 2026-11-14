#!/usr/bin/env python
# coding: utf-8
# In[3]:
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
def is_operator(x):
    return x in "+-*/"
def precedence(x):
    if x in "*/":
        return 2
    if x in "+-":
        return 1
    return 0
# Inx to Postx
def inx_to_postx(exp):
    stack = []
    postx = []
    i = 0
    while i < len(exp):
        if exp[i].isdigit():
            num = ""
            while i < len(exp) and exp[i].isdigit():
                num += exp[i]
                i += 1

            postx.append(num)
            continue
        elif exp[i] == '(':
            stack.append(exp[i])
        elif exp[i] == ')':
            while stack[-1] != '(':
                postx.append(stack.pop())
            stack.pop()
        elif is_operator(exp[i]):
            while (stack and stack[-1] != '(' and
                   precedence(stack[-1]) >= precedence(exp[i])):
                postx.append(stack.pop())
            stack.append(exp[i])
        i += 1
    while stack:
        postx.append(stack.pop())
    return postx
# Build Expression Tree
def build_tree(postx):
    stack = []
    for item in postx:
        node = Node(item)
        if not is_operator(item):
            stack.append(node)
        else:
            node.right = stack.pop()
            node.left = stack.pop()
            stack.append(node)
    return stack.pop()
# In-order Traversal
def inorder(root):
    if root:
        if is_operator(root.value):
            print("(", end="")
        inorder(root.left)
        print(root.value, end="")
        inorder(root.right)
        if is_operator(root.value):
            print(")", end="")
# Pre-order Traversal
def preorder(root):
    if root:
        print(root.value, end=" ")
        preorder(root.left)
        preorder(root.right)
# Post-order Traversal
def postorder(root):
    if root:
        postorder(root.left)
        postorder(root.right)
        print(root.value, end=" ")
# Evaluation
def evaluate(root):
    if not is_operator(root.value):
        return float(root.value)
    left = evaluate(root.left)
    right = evaluate(root.right)
    if root.value == '+':
        return left + right
    elif root.value == '-':
        return left - right
    elif root.value == '*':
        return left * right
    elif root.value == '/':
        return left / right
# Main
expression = input("Enter expression: ")
postx = inx_to_postx(expression)
root = build_tree(postx)
print("\nPostx Expression:", " ".join(postx))
print("In-order   :", end=" ")
inorder(root)
print("\nPre-order  :", end=" ")
preorder(root)
print("\nPost-order :", end=" ")
postorder(root)
print("\nEvaluation :", evaluate(root))
# In[ ]:

