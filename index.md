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

By integrating this consistency condition $\frac{du}{dt} = 0$, we establish the characteristic identity $u(x,t) = f(\xi)$. Substituting this characteristic identity into the path ODE and integrating, we get:

$$\frac{dx}{dt} = f(\xi)$$

$$x(t) = f(\xi)t + \xi$$

From the equation above, we know $x(t)$ is linear.

## Implicit Solution

Starting with the formula $x(t) = f(\xi)t + \xi$ and subbing $f(\xi)$ for $u$, we can rearrange to solve for $\xi$:


$$x(t) = f(\xi)t + \xi$$

$$x(t) = ut + \xi$$

$$\xi = x - ut$$


Substituting this into the characteristic identity, we get the implicit solution of Burgers' Equation:

$$u(x,t) = f(\xi)$$

$$u(x,t) = f(x - ut)$$

$$u(x,t) = 1 + \frac{1}{2}sin(x - ut)$$

Due to this being a transcendental equation, the use of a numeric solver is needed and will be explored in the Numeric Method and Results section of the paper.

## Singularity Analysis

The implicit solution $u(x,t) = f(x - ut)$ remains valid as long as the mapping between the initial coordinate $\xi$ and the spatial coordinate $x$ is one-to-one. As soon as this mapping becomes multivalued, a singularity, or shock, forms and the spatial gradient $u_x$ becomes infinite.

To calculate the spatial gradient $u_x$, we differentiate the implicit solution of Burgers' Equation and rearrange to solve for $u_x$:

$$u(x,t) = f(x - ut)$$

$$u_x = f'(x - ut)(1-tu_x)$$

$$u_x + tf'(x - ut)u_x = f'(x - ut)$$

$$u_x = \frac{f'(x - ut)}{1 + tf'(x - ut)}$$

$$u_x = \frac{f'(\xi)}{1 + tf'(\xi)}$$

$$u_x = \frac{\frac{1}{2}cos(\xi)}{1 + \frac{1}{2}tcos(\xi)}$$

At time $t^* $, when $1 + \frac{1}{2}tcos(\xi) = 0$, $u_x$ becomes infinite and a shock forms. Solving for $t^* $, we first solve for $t$ and then find the infimum of $t$:

$$t = \frac{-2}{cos(\xi)}$$

When $\xi = \pi$, cosine is at its most negative, and $t$ is minimized:

$$t^* = \frac{-2}{cos(\pi)}$$

$$t^* = 2$$

At $t^* = 2$, the particle starting at $\xi = \pi$ becomes the first point in the wave to become vertical, and thus $t^* = 2$ is the Shock Formation Time.

Solving for the Shock Location $x^* $, we substitute $t^* = 2$ and $\xi = \pi$ back into our path equation $x = \xi + f(\xi)t$:

$$x^* = \pi + (1 + 0.5sin(\pi))2$$


$$x^* = \pi + 2$$

$$x^* \approx 5.14$$

The shock first appears at $(x,t) = (\pi + 2,2)$.
