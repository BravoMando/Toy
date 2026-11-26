# DragonFly 代码与文档约定

本文根据当前项目代码归纳排版、目录和构建约定，并保留已明确要求的命名规则。当前没有独立的格式化配置文件；公共头文件和示例已按下述规则整理，尚未实施的 RHI 仍明确标注为草案。

架构职责见 [网格编辑器与 RHI 架构](rhi-architecture.md)，公开声明和调用契约见 [RHI 接口与 ABI](rhi-interfaces.md)。本文件集中维护风格，避免在两份设计文档中重复定义。

## 当前项目依据

| 文件 | 当前实际内容 | 文档如何对应 |
| --- | --- | --- |
| [根 CMakeLists.txt](../CMakeLists.txt) | C/C++ 工程，C++23，Clang/libc++、模块与隐藏符号相关配置 | 内部实现和模块示例按 C++23 编写；不据此宣称所有平台已经构建通过 |
| [DragonFly/CMakeLists.txt](../DragonFly/CMakeLists.txt) | DragonFly 共享库，public 下头文件和模块作为公开文件集，private 下实现参与构建 | SDK 文件继续放在现有 public/private 分层中 |
| [public_core.h](../DragonFly/public/public_core.h) | C 语言链接、编译器识别、导出和 CONTAINER_OF 宏 | 公用宏继续集中于此，接口文档不另建平行的宏体系 |
| [public_api.h](../DragonFly/public/public_api.h) | drawable_base_t 等演示类型与创建/销毁入口 | 它是现有 C 汇总入口；新 RHI 头文件计划由它汇总 |
| [public_api.cppm](../DragonFly/public/public_api.cppm) | 全局模块片段包含头文件，export module public_api，export 块内逐项 using | 模块仍命名 public_api，全局原名重导出 |
| [private_imp.cpp](../DragonFly/private/private_imp.cpp) | import public_api、import std，C++ 分配与回收，C 导出定义 | 作为现有实现示例；新增功能按责任放入 private 子目录 |
| [SandBox/main.cpp](../SandBox/main.cpp) | 通过 import public_api 使用 SDK | 作为 C++ 模块消费示例，不将 SandBox 写成已完成的编辑器 |
| [reference_build.sh](../reference_build.sh) | Linux 路径下 Clang/libc++ 的手工模块构建示例 | 与 CMake 入口分别说明，不用作 Windows/macOS 的通用构建命令 |

根 CMake 尚未设置 C_STANDARD。公共头文件的 C17 语法检查是本文件提出的验证基线；C++23 则已经是项目配置。C++ 模块机制来自 C++20，但本文的工程示例使用项目实际的 C++23 配置。

## 排版

- 代码缩进为两个空格，不使用制表符。嵌套层级每次增加两个空格。
- 函数、结构体、类、联合体和枚举定义的左花括号单独一行；模块保留当前 export { 的形式。
- 指针写为类型与变量之间留空格、星号靠近变量，例如 rhi_device_t *device、const void *data。
- 函数指针统一写为返回类型加 (*名称)，放在 typedef 或函数表字段中；多行参数缩进两个空格。
- 运算符两侧留空格，逗号后留一个空格，例如 rec = new (...)。
- 公开成员按每行一个字段排列，不依赖大段空格做列对齐；短定义也按同样的多行结构展开。
- C 接口的零参数函数写 (void)，避免 C 中 () 的旧式未指定参数含义。
- 语句块之间保留有意义的空行。源代码与文档使用 UTF-8，文件末尾保留换行。

以下仅示范排版，不增加独立的接口契约：

```c
typedef struct rhi_example_t
{
  uint32_t m_struct_size;
  const void *m_data;
} rhi_example_t;

DRAGONFLY_EXPORT_SYMBOL void rhi_example_reset(
  rhi_example_t *self);
```

## 命名

| 对象 | 规则 | 示例 |
| --- | --- | --- |
| 函数、局部变量、参数 | 小写加下划线 | rhi_buffer_release、out_buffer、size_bytes |
| 结构体、类、联合体、类型别名 | 小写加下划线，以 _t 结尾 | rhi_device_t、vk_device_t、draw_function_t |
| 非静态数据成员 | m_ 前缀，包含 C 字段和函数表槽位 | m_base、m_ops、m_size_bytes、m_release |
| C++ 静态数据成员 | s_ 前缀 | s_instance_count |
| 全局变量及命名空间变量 | g_ 前缀，优先内部链接 | g_vk_device_ops |
| 宏和枚举常量 | 大写加下划线 | EXPORT_SYMBOL、CONTAINER_OF、RHI_OK |
| 新增 SDK 文件 | 公开头文件采用 public_ 前缀，功能名小写加下划线 | public_rhi.h、public_rhi_iface.h |
| 实现子目录与新文件 | 按职责使用小写加下划线 | private/rhi/vulkan/、mesh_builder.cpp |

保留现有 DragonFly、SandBox、public_api 等目录、构建目标和模块名称，不因变量命名规则重命名工程目标。现有演示仍使用 create_triangle 等名称；新增 RHI 的函数和类型统一保留 rhi_ 前缀，避免全局名称冲突。

C 结构体必须具有同名 typedef。需要前向声明时先声明 typedef，再单独补全 struct；不在结构体内部声明 typedef，不使用 C++ 继承或虚函数作为公开 C 布局。函数指针类型别名也在文件作用域定义，并采用 _t 后缀。

## 公共头文件与模块

public_core.h 负责公共宏和基础 C 头文件；public_api.h 是汇总入口。RHI 拟分成 public_rhi.h、public_rhi_iface.h、public_rhi_wsi.h，均放在 DragonFly/public。需要对象函数表布局的调用方显式包含 public_rhi_iface.h。

头文件新增或整理时使用 DRAGONFLY_PUBLIC_ 开头的 include guard。C 声明包在 BEGIN_EXTERN_C 与 END_EXTERN_C 中，导出入口使用 EXPORT_SYMBOL。公用头文件不能依赖 import std、C++ 标准库类型、模板、引用、异常或函数重载。

public_api.cppm 在 module; 后包含 C 头文件，再声明 export module public_api。在 export 块里每行一个 using ::名称;，不额外引入包装命名空间，不重复定义 C 类型或转发函数。宏通过头文件使用，不能由 using 导出。

实现文件按现有形式 import public_api 和 import std；需要宏时显式包含 public_core.h。公开声明只在头文件中维护。模块、共享库与消费端的宏条件和导入/导出属性必须分别验证，不能把参考脚本生成的一份 PCM 当作所有工具链通用的二进制接口。

## 公用宏与对象恢复

| 宏 | 约定 |
| --- | --- |
| BEGIN_EXTERN_C / END_EXTERN_C | 包裹 C 声明或定义；C 编译时展开为空 |
| EXTERN_C | 单个 C 链接声明需要时使用；不与已有链接块重复堆叠 |
| DRAGONFLY_EXPORT_SYMBOL | 对应当前共享库的导出/导入策略 |
| BUILD_SDK | 生产 SDK 时由构建目标私有定义；消费端不能照搬设为 1 |
| OFFSET_OF(TYPE, member) | 参数顺序保留，规范实现使用标准 offsetof |
| CONTAINER_OF(TYPE, ptr, member) | 保留现有参数顺序；RHI 对象恢复只用于已经验证的首成员布局 |

RHI 草案使用目标平台默认 C 调用约定，导出函数和槽位保持一致；SDK 与消费端不能通过局部编译选项改变它。需要支持另一调用约定时，在 public_core.h 中统一增加定义并重新验证 ABI，不在各功能头文件中各自增加宏。

CONTAINER_OF 的名字和参数顺序与当前工程一致，但它不承担动态类型识别。传入指针必须来自正确类型对象的对应成员；RHI 的 m_base 规定在偏移零处。C++ 外壳需满足 standard-layout，内部复杂状态通过 m_state 间接持有；用编译期检查约束布局。const 对象的访问不能借宏去掉只读约束后修改。

## 文档如何保持一致

- 架构文档写职责、数据流、目录、并行和实现阶段；接口文档写声明、ABI、所有权与调用契约。
- 当前文件使用相对链接指向真实源码；未创建的文件明确标注为规划，不写成已存在的实现。
- 接口代码块统一使用现有宏、两空格缩进和项目模块入口。节选说明所属头文件及上下文，不能让读者误认为每块都可独立编译。
- UML 类型与成员遵守同一命名规则。Mermaid 使用两个空格表达嵌套；图的语法规则优先于 C/C++ 花括号规则。
- 示例与实际代码不一致时，说明差异和待完成项，不宣称修改文档就已经修复源码。
- 架构、接口和本规范各维护自己的内容，通过链接关联，不复制多份 C 声明或 ABI 规则。

## 当前实现与验证

| 项目 | 已完成的修正 |
| --- | --- |
| 公用宏 | 两个公开头文件添加 include guard；__cplusplus 和 BUILD_SDK 安全判断；Windows 使用正确的 __declspec 导入/导出，GNU/Clang 的非 Windows 路径使用可见性属性 |
| C 兼容 | draw_function_t 移到文件作用域并由模块重导出；零参数函数声明统一为 (void) |
| 成员与布局 | m_draw、m_base、m_verts、m_org；OFFSET_OF 使用 offsetof；C++ 实现检查 standard-layout 与首成员偏移 |
| 生命周期 | 创建时零初始化几何并设置绘制回调，分配失败返回空指针；配对销毁函数接受空指针；C++ 通过已检查的首成员转换回收对象 |
| C++ 异常边界 | 当前 POD 创建使用不抛出分配，演示回调使用 std::puts；不从这些示例 C 入口传播分配或格式化异常 |

绘制回调目前只输出形状名称，是分派演示，不是 Vulkan 绘制实现。成员改名后，消费方应相应使用 m_ 字段；创建/销毁函数的 C 符号名称保持不变。
