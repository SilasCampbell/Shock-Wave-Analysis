---
title: Abstract
layout: single
mathjax: true
---

We study a prototypical shock-wave PDE and compare analytical predictions with numerical experiments.

## What’s here
- Model PDE
- Theoretical analysis
- Numerical method + results
- Reproducibility instructions

# Model PDE

## Setup

Burgers' Equation (Inviscid):

$$u_t + u \cdot u_x = 0$$

Cauchy Data:

$$f(x) = 1 + \frac{1}{2}\sin(x)$$

## The Method of Characteristics



Total Derivative:

$$\frac{du}{dt} = \frac{\partial u}{\partial t} + \frac{dx}{dt}\frac{\partial u}{\partial x}$$

We set the path $\frac{dx}{dt} = u$. By choosing the path $\frac{dx}{dt} = u$, we force the total derivative $\frac{du}{dt}$ to be equal to 0, making $u$ invariant along the characteristic curve. This reduces the PDE into a pair of ODE's.

## Solving the Characteristic Equations

The system of ODE's derived from the Method of Characteristics is:

- $\frac{du}{dt} = 0$ (the velocity ODE)
- $\frac{dx}{dt} = u$ (the path ODE)

Integrating the velocity ODE, we find that $u$ remains constant along the characteristic curve and it's value is determined by its initial value at the starting position $\xi$:

$$u(x,t) = f(\xi)$$

Substituting in this consistency condition and integrating the path ODE, we get:

$$\frac{dx}{dt} = f(\xi)$$
$$x(t) = f(\xi)t + \xi$$

From the equation above, we know $x(t)$ is linear.

## Implicit Solution

Starting with the formula $x(t) = f(\xi)t + \xi$, we can rearrange to solve for $\xi$:

$$\xi = x - ut$$

Substituting this into the consistency condition, we get the implicit solution of Burgers' Equation:

$$u(x,t) = f(\xi)$$
$$u(x,t) = f(x -ut)$$
$$u(x,t) = 1 + \frac{1}{2}sin(x - ut)$$





