2015年11月28日（灵感来自：https://github.com/jvaelen/2048）：
1. 修改了程序结构，将程序分为QT-GUI和CORE部分。
2. 采用观察者模式，core通过notify调用Observer的onSubjectChanged通知GUI变化，
	而不用GUI每次主动检测core的变更。
3. 修改了上一版本TetrisGameWindow类成员game内存泄露问题
4. TetrisGame的up、down、left、right、timeout做了一些调整
5. 添加了更多注释
6. 修改了命名风格
