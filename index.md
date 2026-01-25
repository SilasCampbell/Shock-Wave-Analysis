---
title: Abstract
layout: single
mathjax: true
---

We study a prototypical shock-wave PDE and compare analytical predictions with numerical experiments.

# Model PDE

## Setup

Burger's Equation (Inviscid):

$$u_t + u \cdot u_x = 0$$

Cauchy Data:

$$f(x) = 1 + \frac{1}{2}\sin(x)$$

## The Method of Characteristics

$$\frac{du}{dt} = \frac{\partial u}{\partial t} + \frac{dx}{dt}\frac{\partial u}{\partial x}$$

We set the path $\frac{dx}{dt} = u$. Comparing this to Burger's Equation, we can conclude that the velocity along this path must be constant: $\frac{du}{dt} = 0$

By choosing the path $\frac{dx}{dt} = u$, u is invarient along the characteristic curve. This reduced the PDE into a pair of ODE's.

The resulting characteristic system is:
\begin{enumerate}
    \item $\frac{dx}{dt} = u$ (The path equation)
    \item $\frac{du}{dt} = 0$ (The consistency condition)
\end{enumerate}



## What’s here
- Model PDE
- Theoretical analysis
- Numerical method + results
- Reproducibility instructions



