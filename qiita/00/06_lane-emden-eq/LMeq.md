# 06 Lane-Emden eq.

## Lane-Emden eq. の数値解法

Lane-Emden 方程式は以下の式で与えられる：
$$\frac{1}{\xi^2}\frac{d}{d\xi}\left(\xi^2\frac{d\theta}{d\xi}\right)=-\theta^n$$

ここでは, Lane-Emden eq.を次の2本の式に分けて扱う：
$$\frac{d\theta}{d\xi}=-\frac{\mu}{\xi^2}$$
$$\frac{d\mu}{d\xi}=\xi^2\theta^n$$

ここでは有限差分法を用いて実装するが, $\xi=0$で特異点になっているため, 原点からちょっと進んだ点$\xi=\epsilon$を初期値として始める。具体的に展開したものを以下に記しておく：
$$\theta=1-\frac{1}{6}\epsilon^2+\frac{n}{120}\epsilon^4+O(\epsilon^4)$$
$$\mu=\frac{1}{3}\epsilon^3-\frac{n}{30}\epsilon^5+O(\epsilon^7)$$

## Lane-Emden eq. の解析解

### $N=0$のとき
これは普通に積分できて, 
$$\theta=1-\frac{1}{6}\xi^2$$

### $N=1$のとき
$z=\xi\theta$という変数変換をしてやると調和振動子の微分方程式になってくれて, 
$$\theta=\frac{\sin\xi}{\xi}$$

### $N=5$のとき
なぜか解ける。$f=\frac{1}{\theta^2}$に変形して級数解を求める。これは有限で止まって, 打ち切られた解は, 
$$\theta=\left(1+\frac{\xi^2}{3}\right)^{-1/2}$$