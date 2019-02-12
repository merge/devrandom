#!/bin/bash
echo "## networking todos" > README.md
echo "[http://vger.kernel.org/~davem/net_todo.html](http://vger.kernel.org/~davem/net_todo.html)" >> README.md
echo "" >> README.md
echo "## networking todos" >> README.md
echo "[http://vger.kernel.org/~davem/net_todo.html](http://vger.kernel.org/~davem/net_todo.html)" >> README.md
echo "" >> README.md
echo "## RCU todos" >> README.md
echo "[https://www.kernel.org/pub/linux/kernel/people/paulmck/rcutodo.html](https://www.kernel.org/pub/linux/kernel/people/paulmck/rcutodo.html)" >> README.md
echo "" >> README.md
echo "## kernel janitors todos" >> README.md
echo "* [https://code.google.com/archive/p/kernel-janitors/wikis/TODO.wiki](https://code.google.com/archive/p/kernel-janitors/wikis/TODO.wiki)" >> README.md
echo "* [https://kernelnewbies.org/KernelJanitors/Todo](https://kernelnewbies.org/KernelJanitors/Todo)" >> README.md
echo "" >> README.md
echo "## TODO files across the tree" >> README.md
for file in $(find . -name \*TODO\*); do
	echo "* [${file}](https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git/tree/${file})" >> README.md
done
