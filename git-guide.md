# Git 完整操作指南（从零开始）

> 适用于：Windows + Hexo 博客 + GitHub Pages
> 账号：Candywo1F

---

## 一、初始化仓库

### 1.1 创建本地仓库

```bash
git init
```

**作用：** 在当前文件夹创建 `.git` 隐藏目录，初始化 Git 仓库。执行后文件夹变成 Git 仓库。

### 1.2 查看状态

```bash
git status
```

**作用：** 查看哪些文件被修改、哪些未跟踪。输出示例：
```
Untracked files:
  _config.yml
  source/
  ...
```

---

## 二、暂存与提交

### 2.1 暂存文件

```bash
git add .                    # 暂存所有修改的文件
git add _config.yml          # 只暂存某个文件
git add source/              # 只暂存某个文件夹
```

**作用：** 把文件放入"暂存区"（Staging Area），准备提交。注意：`add` 和 `.` 之间必须有空格。

### 2.2 提交到本地仓库

```bash
git commit -m "Initial commit"
```

**作用：** 把暂存区的内容提交到本地仓库，`-m` 后面是提交信息（备注）。

### 2.3 查看提交历史

```bash
git log                      # 查看提交记录
git log --oneline            # 简洁版
```

---

## 三、关联远程仓库

### 3.1 添加远程仓库地址

```bash
git remote add origin https://github.com/Candywo1F/Candywo1F.github.io.git
```

**作用：** 给远程仓库起个别名 `origin`，方便后续操作。URL 可以是 HTTPS 或 SSH。

### 3.2 查看远程仓库

```bash
git remote -v
```

**输出：**
```
origin  git@github.com:Candywo1F/Candywo1F.github.io.git (fetch)
origin  git@github.com:Candywo1F/Candywo1F.github.io.git (push)
```

### 3.3 修改远程仓库地址

```bash
# 改为 SSH
git remote set-url origin git@github.com:Candywo1F/Candywo1F.github.io.git

# 改为 HTTPS
git remote set-url origin https://github.com/Candywo1F/Candywo1F.github.io.git
```

---

## 四、推送与拉取

### 4.1 首次推送

```bash
git push -u origin main
```

**作用：** 把本地 `main` 分支推送到远程 `origin`，`-u` 设置上游分支（之后可直接 `git push`）。

### 4.2 日常推送

```bash
git push                     # 推送到默认分支
git push origin main         # 明确指定分支
```

### 4.3 拉取远程更新

```bash
git pull                     # 拉取并合并
git pull origin main         # 明确指定分支
```

### 4.4 合并不相关历史

```bash
git pull origin main --allow-unrelated-histories
```

**作用：** 本地和远程是两个独立仓库（无共同历史）时，允许合并。

---

## 五、分支管理

### 5.1 查看分支

```bash
git branch                   # 查看本地分支
git branch -a                # 查看所有分支（含远程）
```

### 5.2 创建/切换分支

```bash
git branch feature            # 创建分支
git checkout feature         # 切换分支
git checkout -b feature      # 创建并切换（一步）
git switch feature           # 新版切换命令
```

### 5.3 重命名分支

```bash
git branch -M main           # 重命名当前分支为 main
```

### 5.4 合并分支

```bash
git merge feature            # 把 feature 合并到当前分支
```

---

## 六、SSH 密钥配置

### 6.1 生成密钥

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

**作用：** 生成 SSH 密钥对，公钥用于 GitHub 认证。

### 6.2 查看公钥

```bash
# Windows
type %USERPROFILE%\.ssh\id_ed25519.pub

# Mac/Linux
cat ~/.ssh/id_ed25519.pub
```

### 6.3 添加到 GitHub

GitHub → Settings → SSH and GPG keys → New SSH key → 粘贴公钥

### 6.4 配置 SSH

编辑 `~/.ssh/config`：
```
Host github.com
    Hostname ssh.github.com
    Port 443
    User git
    IdentityFile ~/.ssh/id_ed25519
```

### 6.5 测试连接

```bash
ssh -T git@github.com
```

**成功输出：** `Hi Candywo1F! You've successfully authenticated...`

---

## 七、常见错误与解决

### 7.1 `git: 'add.' is not a git command`

**原因：** `git add` 和 `.` 之间缺少空格
**解决：** `git add .`

### 7.2 `src refspec main does not match any`

**原因：** 没有 commit，分支不存在
**解决：** 先 `git add .` → `git commit -m "msg"` → 再 push

### 7.3 `Failed to connect to github.com:443`

**原因：** 网络问题或代理
**解决：**
```bash
# 设置代理
git config --global http.proxy http://127.0.0.1:7890
# 或改用 SSH
git remote set-url origin git@github.com:用户/仓库.git
```

### 7.4 `Permission denied to deploy key`

**原因：** 使用的是 Deploy Key（只读），不是账号密钥
**解决：** 改用账号 SSH 密钥（id_ed25519）

### 7.5 `rejected... fetch first`

**原因：** 远程有内容本地没有
**解决：**
```bash
git pull origin main --allow-unrelated-histories
git push -u origin main
```

### 7.6 `fatal: unable to access`

**原因：** HTTPS 认证失败（GitHub 不再支持密码）
**解决：** 用 Personal Access Token 替代密码，或改用 SSH

---

## 八、日常操作速查

```bash
# 查看状态
git status

# 暂存所有修改
git add .

# 提交
git commit -m "描述修改内容"

# 推送
git push

# 拉取
git pull

# 查看日志
git log --oneline

# 撤销未暂存的修改
git checkout -- <文件名>

# 撤销已暂存的文件
git reset HEAD <文件名>

# 查看差异
git diff
```

---

## 九、.gitignore 配置

Hexo 项目应该忽略以下文件：

```
node_modules/
public/
.deploy_git/
db.json
*.log
.DS_Store
```

**作用：** 告诉 Git 哪些文件不需要跟踪。

---

## 十、完整流程回顾（本次操作）

```bash
# 1. 初始化
git init

# 2. 暂存并提交
git add .
git commit -m "Initial commit"

# 3. 重命名分支
git branch -M main

# 4. 关联远程仓库
git remote add origin git@github.com:Candywo1F/Candywo1F.github.io.git

# 5. 推送（首次需合并远程内容）
git pull origin main --allow-unrelated-histories
git push -u origin main
```

---

*文档生成时间：2026-11-22*
*账号：Candywo1F*
*仓库：Candywo1F.github.io*