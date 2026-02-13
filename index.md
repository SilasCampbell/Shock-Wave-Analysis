---
title: Abstract
layout: single
mathjax: true
---



## What’s here
- Model PDE
- Weak Solutions
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

Due to this being a transcendental equation, the equation cannot be simplified any further and must remain in this implicit form.

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

The shock first appears at:

$$(x,t) = (\pi + 2,2)$$

After $t^* = 2$, the implicit soltution becomes multivalued, and weak solutions are needed to reconcile this.

# Weak Solutions

In Burger's equation, $u_t + u \cdot u_x = 0$, $u_x$ is only valid before $t^* = 2$. Because of this, the first thing we will do is put Burger's equation in its conservative form:

$$\frac{\partial u}{\partial t} + \frac{\partial}{\partial x}(\frac{1}{2} u^2) = 0$$

This form does not assume that $u$ is differentiable. To further elaborate why this form is needed, first we integrate where $\frac{1}{2} u^2 = F(u)$:

$$
\begin{aligned}
\int_{x_1}^{x_2} \left[ \frac{\partial u}{\partial t} + \frac{\partial}{\partial x} F(u) \right] dx &= 0 \\
\int_{x_1}^{x_2} \frac{\partial u}{\partial t} dx + \int_{x_1}^{x_2} \frac{\partial}{\partial x} F(u) dx &= 0 \\
\frac{d}{dt} \int_{x_1}^{x_2} u(x,t) dx + F(u(x_2,t)) - F(u(x_1,t)) &= 0
\end{aligned}
$$

Rearranging to isolate the rate of change, we get the integral form of this conservation law:

$$\frac{d}{dt} \int_{x_1}^{x_2} u(x,t) \, dx = F(u(x_1,t)) - F(u(x_2,t))$$

The LHS shows the rate of change of the area under the curve on the domain $[x_1,x_2]$, and the RHS shows that this change equals what flows into the left boundary, minus what flows out of the right boundary. Note that this is unaffected by the discontinuity that may be contained by the boundary values.

## Deriving the Weak Formulation

The equation previously derived is a global statement about conservation. To derive a local statement that accounts for discontinuities like shocks, we introduce a test function $v(x,t)$ with compact support, denoted $\text{supp}(v)$. This means $v(x,t)$ is a smooth, infinitely differentiable function with compact support defined on $\text{supp}(v) \subset \Omega$ where $\Omega = \mathbb{R} \times [0,\infty)$, and v(x,t) is zero on the boundary $\partial \Omega$. By first multiplying the conservative form of Burgers' equation by $v(x,t)$ and then integrating, we don't have to worry about a discontinuous increase of one of the boundary values.

$$\iint_{\Omega} (\frac {\partial u}{\partial t} + \frac {\partial}{\partial x}[\frac{1}{2} u^2])\ v(x,t)\ dt\ dx = 0$$

Now we define a vector field $\mathbf{U}$ in the $(x,t)$ plane:

$$\mathbf{U} = \begin{pmatrix} \frac{1}{2}u^2 \\ u \end{pmatrix}$$

Noticing that $\nabla \cdot \mathbf{U} = \frac {\partial u}{\partial t} + \frac {\partial}{\partial x}[\frac{1}{2} u^2]$, we substitute this into our integral:

$$\iint_{\Omega} v(\nabla \cdot \mathbf{U})\ dt\ dx = 0$$

Using the formula $\nabla \cdot (v \mathbf{U}) = v  (\nabla \cdot \mathbf{U}) + \mathbf{U} \cdot \nabla v$, we rearrange and substitute this into the integral:

$$\iint_{\Omega} \nabla \cdot (v \mathbf{U})\ dt\ dx - \iint_{\Omega} \mathbf{U} \cdot \nabla v\ dt\ dx = 0$$

By Green's Theorem,

$$\iint_{\Omega} \nabla \cdot (v \mathbf{U})\ dt\ dx = \oint_{\partial \Omega} v \mathbf{U} \cdot \mathbf{n}\ \mathbf{ds}$$

Where $\mathbf{n}$ is the outward unit normal vector of the boundary and $\mathbf{ds}$ is the infinitesimal arc length. Because $v(x,t)$ has compact support and is defined to be zero on the boundary $\partial \Omega$, this line integral equals zero:

$$\iint_{\Omega} \nabla \cdot (v \mathbf{U})\ dt\ dx = 0$$

$$\implies \iint_{\Omega} \mathbf{U} \cdot \nabla v\ dt\ dx = 0$$

$$\implies \iint_{\Omega} [u \frac {\partial v}{\partial t} + \frac{1}{2} u^2 \frac {\partial v}{\partial x}]\ dt\ dx = 0$$

This final equation aligns with the definition of the weak solution to Burgers' equation in Introduction to Partial Differential Equations by Olver (2016):

Definition: A function $u(t,x)$ is said to be a weak solution to the nonlinear transport equation if:

$$\iint_{\Omega} \left( u \frac{\partial v}{\partial t} + \frac{1}{2}u^2 \frac{\partial v}{\partial x} \right) dt \, dx = 0 \quad \text{}$$

for all $C^1$ functions $v(t,x)$ with compact support such that $\text{supp } v \subset \Omega$.

By shifting the requirement of differentiability from the solution $u$ to the test function $v$, we have established a mathematical framework that remains physically consistent after the Shock Formation Time. While the weak formulation previously derived allows for the existence of shock solutions, it does not account for uniqueness. In many cases, multiple weak solutions can satisfy the same initial conditions, so to find the physically relevant weak solutions, we would add extra constraints like the entropy condition. While these concepts are crucial for a more thorough analysis of shock wave theory, they remain beyond the scope of this particular project.

## The Rankine-Hugoniot Condition

Having now derived a weak solution, we can apply this equation to determine the speed at which the shock propagates. We consider a domain $\Omega$ with a single jump discontinuity along a smooth curve $\mathbf{C}$ parameterized by $x = \sigma (t)$. This curve bisects our domain into two subdomains: $\Omega_+ \text{ and } \Omega_-$. We define:

$$u_+ = u \mid_{\Omega_+}, \text{ which lies above } \mathbf{C}$$

$$u_- = u \mid_{\Omega_-}, \text{ which lies below } \mathbf{C}$$

$u_+ \text{ and } u_-$ are classical solutions on their respective domains. Now we partition the weak solution integral across two sub-domains:

$$\iint_{\Omega_-} \left( u_- \frac{\partial v}{\partial t} + \frac{1}{2}u_-^2 \frac{\partial v}{\partial x} \right) dt \ dx + \iint_{\Omega_+} \left( u_+ \frac{\partial v}{\partial t} + \frac{1}{2}u_+^2 \frac{\partial v}{\partial x} \right) dt \ dx = 0$$

Using Green's Formula:

$$0 = \oint_{\partial \Omega_-} (\mathbf{U_-} \cdot \mathbf{n_-}) v \ ds - \iint_{\Omega_-} \left( (u_-)_t + (u_-^2)_x \right) v \ dt \ dx$$ 
$$+ \oint_{\partial \Omega_+} (\mathbf{U_+} \cdot \mathbf{n_+}) v \ ds - \iint_{\Omega_+} \left( (u_+)_t + (u_+^2)_x \right) v \ dt \ dx$$

Because $u_- \text{ and } u_+$ are classical soultions, $u_t + (\frac{1}{2} u^2)_x = 0$ and the integral collapses to:

$$0 = \oint_{\partial \Omega_-} (\mathbf{U_-} \cdot \mathbf{n_-}) v \ ds + \oint_{\partial \Omega_+} (\mathbf{U_+} \cdot \mathbf{n_+}) v \ ds$$

Because $v$ has compact support and equals $0$ on the outer boundary $\partial \Omega$, the only remaining part of the integral lies on the shock curve $\mathbf{C}$:

$$0 = \oint_{\mathbf{C}} (\mathbf{U_-} \cdot \mathbf{n_-} + \mathbf{U_+} \cdot \mathbf{n_+}) v \ ds$$

Since $\mathbf{n}$ represents the outward normal of $\mathbf{C}$, $\mathbf{n_-} = -\mathbf{n_+}$. Substituting this in, we get:

$$0 = \oint_{\mathbf{C}} (\mathbf{U_-} - \mathbf{U_+}) \cdot \mathbf{n_-} v \ ds$$

To solve for $\mathbf{n_-}$, we first parameterize the shock curve $\mathbf{C}$ as $G(x,t) = x - \sigma (t) = 0$. The gradient of $G$ will be normal to $\mathbf{C}$ and will be the value of $\mathbf{n_-}$. 

$$\nabla G = \left( \frac{\partial G}{\partial x}, \frac{\partial G}{\partial t} \right) = (1, -\dot{\sigma}(t))$$

Substituting this in and calculating the dot product:

$$0 = \oint_{\mathbf{C}} (\mathbf{U_-} - \mathbf{U_+}) \cdot (1, -\dot{\sigma}(t)) v \ ds$$
$$0 = \oint_{\mathbf{C}} \left[ \left( \frac{1}{2}u_-^2 - \frac{1}{2}u_+^2 \right) - \dot{\sigma}(t)(u_- - u_+) \right] v \ ds$$

Since this integral must equal zero for any arbitrary smooth test function $v$ with compact support, the term inside the brackets must vanish along the curve $\mathbf{C}$:

$$\left( \frac{1}{2}u_-^2 - \frac{1}{2}u_+^2 \right) - \dot{\sigma}(t)(u_- - u_+) = 0$$

We now isolate the shock speed, $s = \dot{\sigma}(t)$:

$$\dot{\sigma}(t)(u_- - u_+) = \frac{1}{2}u_-^2 - \frac{1}{2}u_+^2$$
$$s = \frac{\frac{1}{2}u_-^2 - \frac{1}{2}u_+^2}{u_- - u_+}$$

Using the difference of squares $(\frac{1}{2}(u_- - u_+)(u_- + u_+))$, the expression simplifies to the final jump condition for Burgers' equation:

$$s = \frac{u_- + u_+}{2}$$

This result, the Rankine-Hugoniot condition, shows that the shock wave propogates at the average velocity of the state immediately ahead of and behind the discontinuity.

# Numerical Methods

To simulate the evolution of the solution past the shock-formation time, we implement the Lax–Wendroff scheme, a second-order accurate finite difference method for nonlinear conservation laws. We begin from the conservative form of Burgers’ equation: $u_t + \left( \frac{1}{2}u^2 \right)_x = 0$, which can be written in general conservation form as:

$$u_t + f(u)_x = 0, \ \text{where} \ f(u) = \frac{1}{2}u^2$$

## The Lax–Wendroff Scheme for Conservation Laws

The Lax–Wendroff method is derived from a second-order Taylor expansion in time:

$$u_i^{n+1} = u_i^n + \Delta t(u_t)_i^n + \frac{\Delta t^2}{2}(u_{tt})_i^n$$

From the PDE, we can substitute the first temporal derivative:

$$u_t = -f(u)_x$$Differentiating once more with respect to time to find the second-order term:$$u_{tt} = -\frac{\partial}{\partial t}(f(u)_x) = -\frac{\partial}{\partial x}(f(u)_t)$$

Using the chain rule:

$$f(u)_t = f'(u)u_t$$

Substituting $u_t = -f(u)_x$ back into the expression:

$$u_{tt} = \frac{\partial}{\partial x}(f'(u)f(u)_x)$$

Thus, the Taylor expansion becomes:

$$u_i^{n+1} = u_i^n - \Delta t(f(u)_x)_i^n + \frac{\Delta t^2}{2} \left[ \frac{\partial}{\partial x}(f'(u)f(u)_x) \right]_i^n$$

## Discretization Used in the Code

For Burgers’ equation, $f(u) = \frac{1}{2}u^2$, so the Jacobian is:

$$f'(u) = u$$

The spatial derivative of the flux is expanded using the chain rule:

$$(f(u)_x)_i^n = \frac{\partial}{\partial x} \left( \frac{1}{2} u^2 \right)_i^n = \left( u \frac{\partial u}{\partial x} \right)_i^n$$

Approximating $\frac{\partial u}{\partial x}$ with a first-order central difference, we get:

$$(f(u)_x)_i^n \approx u_i^n \left( \frac{u_{i+1}^n - u_{i-1}^n}{2\Delta x} \right)$$

For the second-order term, we approximate the nested derivative $\frac{\partial}{\partial x} [f'(u) f(u)_x]$. Substituting $f'(u) = u$ and $f(u)_x = u \frac{\partial u}{\partial x}$, the term becomes:

$$[\frac{\partial}{\partial x} (u^2 \frac{\partial u}{\partial x})]_i^n$$

By evaluating the wave speed $u^2$ locally at grid point $i$, making $u^2$ act like a constant, and applying a second-order central difference to the second partial derivative, we obtain:

$$[ \frac{\partial}{\partial x} (u^2 \frac{\partial u}{\partial x})]_i^n \approx (u_i^n)^2 (\frac{\partial^2 u}{\partial x^2}) \approx (u_i^n)^2 \left( \frac{u_{i+1}^n - 2u_i^n + u_{i-1}^n}{\Delta x^2} \right)$$

After substitution, the formula reduces to the quasilinear Lax–Wendroff form:

$$u_i^{n+1} = u_i^n - \frac{1}{2}(\frac{u_i^n \Delta t}{\Delta x})(u_{i+1}^n - u_{i-1}^n) + \frac{1}{2} (\frac{u_i^n \Delta t}{\Delta x})^2 (u_{i+1}^n - 2u_i^n + u_{i-1}^n)$$

## Implementation

In the code, we define the local Courant number:

$$c_i = \frac{u_i^n \Delta t}{\Delta x}$$

In the program:

$$\Delta x \approx 0.002$$
$$\Delta t = 10^{-4}$$
$$\text{max} |u| = 1.5$$

So the CFL condition is met and $|c_i| < 1$

The final formulation used in the simulation becomes:

$$u_i^{n+1} = u_i^n - \frac{1}{2}c_i(u_{i+1}^n - u_{i-1}^n) + \frac{1}{2}c_i^2(u_{i+1}^n - 2u_i^n + u_{i-1}^n)$$

