# c2html_mac
mac 版本的 linux 源代码转网页的代码.对应 antriver.com, 包括函数交叉索引文件生成

本软件由icecut (姜亦春)icecut@qq.com 开源. 随便使用.不保留版权.

2014年,为了让大家能讨论好 linux 学习,制作了一个网站,来帮助大家
样例:
http://antriver.com/linux/src/linux-3.15.7/Documentation/timers/hrtimers.txt.html

这个网站看起来和 lxr 相似.但是,在用户体验上进行了现代互联网的设计.更趋向与 web 应用程序.
lxr 的缺点是函数索引的跳转需要你自己判断.我的程序根据 c 语言去分析,减少了可选项,
但是还没有精确到所有函数都能跳转.在 web 上,绑定了添加注释功能.但是由于参与的人不多.
还是我自己维护了一些注释.

经历了多年以后,创业项目虽然还有一丝生命,或许在未来还有希望.但是我更愿意开源,
因为很多人都说代码烂,却没人知道好的代码是什么样子.我刚毕业就职在方正的it 事业部,
跟随王老师做项目,从0开始做了一个项目12人年的项目大小.从那之后,我的代码就一直严格要求,

虽然你在这个源代码 c 2 html 工程中,看不到所有的提交进度,是因为我有多次改版了.
以前用 i7 920的 cpu, 用24G 内存,配合 vs, 现在换了 mbp, i7 + 16G 内存,所以最新版是 mac 的
不过不用担心,自己建一个工程,添加进去就好了.

也许,一个好的项目给一个初学者,依旧是看不懂的.

可能我也会拍一下视频培训吧,毕竟时间是成本,培训就不免费了.

欢迎关注我都订阅号: 蚂蚁河技术

欢迎访问我的百度传课培训页面:http://www.chuanke.com/s3359313.html
现有嵌入式的培训,都是低于市场价存在的.毕竟是我的 z 计划.

欢迎到 http://antriver.com 的源代码阅读页面去点评 linux 源代码.当然以辅助初学者更好学习为目标.

另外我都版本3.15.7看起来不是最新的,但我考虑根据 linux 的 git 解析,就能将老的评点追加到新的版本上去,这个功能我一直没有做.
也许考虑是不是用 golang 来实现一下.毕竟更轻量级.而且对于新的代码,我的信心是不足的,我虽然对我的代码还是有信心的,
但是我没有那么多时间....

代码量
 ls |xargs cat |wc -l
    4131
