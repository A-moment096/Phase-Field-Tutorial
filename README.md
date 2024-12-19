# 相场模拟培训课件与资料

From: *中南大学 杜勇教授课题组 2024相场培训*

欢迎了解我们的开源相场模拟软件 **MInDes**

Github仓库：https://github.com/Microstructure-Intelligent-Design/MInDes

# 使用方法

本仓库存放了培训过程中使用到的Beamer课件，对应的 $\LaTeX$ 源文件，以及部分别的资源。欢迎PR, 欢迎对内容批评指正。

每个文件夹都有的内容：
- `.tex` 文件：可以由此编译生成文件夹中的 `.pdf` 文件。使用 pdfLaTeX 进行编译即可；
- `.pdf` 文件：本教程使用的幻灯片。视频中使用 [SumatraPDF](https://www.sumatrapdfreader.org/free-pdf-reader) 的演示模式播放；
- `pic` 文件夹：生成幻灯片需要的图片；

其余内容在对应的[内容简介](#内容简介)中介绍。

# 视频链接

- [PF_T1: Introduction and Mathematics 1](https://www.bilibili.com/video/BV1961uYiEpJ/)
- [PF_T2: Mathematics 2: Numerical Methods with Python Implementation](https://www.bilibili.com/video/BV16jDVYTEbY/)
- [PF_T3: C++ Programming and Calculation Examples](https://www.bilibili.com/video/BV15aSuY2EpY/)
- [PF_T4: Phase Field Simulation of Spinodal Decomposition](https://www.bilibili.com/video/BV13niUYnEMu/)
- [PF_T5: Phase Field Simulation of Grain Growth](https://www.bilibili.com/video/BV1961uYiEpJ/)

# 内容简介

## PF_T1: Introduction and Mathematics 1

介绍了相场法的基本情况，包括：
- 相场，场变量
- Cahn-Hilliard 方程 与 Allen-Cahn 方程

以及本教程需要或可能需要的数学基础，包括：
- Talyor 展开
- 条件极值
- 变分导数 （泛函导数）
- 向量微积分

## PF_T2: Mathematics 2: Numerical Methods with Python Implementation

介绍了为求解相场所需要的算法，包括：
- 数值微分方程
- 数值积分
- 梯度算符 （求导）
- Laplacian 算符

为了实现这些算法，粗略介绍了 Python 的相关内容，并使用 Python 进行算法实现。

**附件**：
- `Calculation with Python.ipynb`：Python 语法介绍和算法实现。使用 Python 版本为 >3.10，需要安装 `numpy` 库和 `matplotlib` 库。


## PF_T3: C++ Programming and Calculation Examples

粗略介绍了 C++ 编程语言，并且使用 C++ 实现了前述的算法，以及使用 C++ 编程模拟传热方程

**附件**：
- `src` 文件夹：存有介绍 C++ 语法的 C++ 源文件。采用 C++17 标准。
- `read` 文件夹：基于 `src` 文件夹中内容对应的 MarkDown 文件便于阅读。

## PF_T4: Phase Field Simulation of Spinodal Decomposition

介绍了调幅分解过程的热力学基础以及其适用的相场模型/方程，并使用 C++ 进行模拟。

**附件**
- `AB_free_energy.py`：绘制双势阱曲线的 Python 代码。使用 Python 版本为 >3.10，需要安装 `numpy` 库和 `matplotlib` 库。
- `AB_free_energy.cpp`：本节内容中用以模拟调幅分解所使用的 C++ 代码。采用 C++17 标准。

## PF_T5: Phase Field Simulation of Grain Growth

介绍了晶粒长大的热力学过程以及其适用的相场模型/方程，并使用 C++ 进行模拟。

**附件**
- `double_grain.cpp`：本节内容中用以模拟晶粒长大所使用的 C++ 代码。 采用 C++17 标准。