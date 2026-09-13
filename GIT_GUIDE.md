# Git 与 GitHub 使用指南

## 1. Git 基础流程

在项目目录打开终端，依次执行：

```powershell
git status
git add .
git commit -m "描述本次修改"
git push
```

推荐保持一个清晰、单一的提交目的。例如：

```powershell
git commit -m "docs: 补充安装说明"
```

## 2. 绑定 GitHub 仓库

先在 GitHub 网页端创建一个**空仓库**。如果网页端已经创建了 README、`.gitignore` 或 License，请使用下面的“本地已有提交”方案。

### 本地已有提交

```powershell
git remote add origin https://github.com/你的用户名/仓库名.git
git push -u origin main
```

如果 `origin` 已存在，可改用：

```powershell
git remote set-url origin https://github.com/你的用户名/仓库名.git
git push -u origin main
```

### 检查远程绑定

```powershell
git remote -v
git branch -vv
```

## 3. 日常修改流程

```powershell
git pull --rebase
git status
git add .
git commit -m "说明本次修改"
git push
```

如果团队成员直接修改同一个分支，先拉取再推送可以减少冲突。

## 4. 分支流程

```powershell
git switch -c feature/example
git add .
git commit -m "feat: 添加示例功能"
git push -u origin feature/example
```

完成开发后，在 GitHub 上创建 Pull Request，合并后删除远程功能分支。

## 5. Visual Studio 中使用 Git

> 以下指 Microsoft Visual Studio（不是 Visual Studio Code）。如果使用 VS Code，请参考第 6 节。

1. 打开 Visual Studio，点击 `文件 > 打开 > 文件夹`，选择本仓库目录。
2. 打开 `Git > 管理分支`，确认当前分支为 `main`。
3. 修改文件后，打开 `Git 更改` 窗口。
4. 在“更改”列表中检查文件，填写提交消息，点击“提交全部”。
5. 点击顶部 Git 状态栏或 `Git > 同步`，选择“推送”或“提取”。
6. 点击 `Git > 管理远程存储库`，确认 `origin` 指向 GitHub 地址。
7. 如需新分支，在 `Git > 新建分支` 创建，完成后推送并创建 Pull Request。

Visual Studio 中常见按钮含义：

- **提取/Pull**：下载远程更新。
- **推送/Push**：上传本地提交。
- **同步/Sync**：通常先提取，再推送。
- **提交/Commit**：只保存到本地 Git，不会上传 GitHub。
- **暂存/Stage**：选择本次提交包含的文件。

## 6. Visual Studio Code 中使用 Git

1. 用“打开文件夹”打开本仓库。
2. 点击左侧“源代码管理”图标，或按 `Ctrl+Shift+G`。
3. 在更改列表中将文件加入暂存区。
4. 输入提交消息，点击“提交”。
5. 点击“同步更改”或“推送”。
6. 通过左下角分支名称切换、创建和发布分支。

## 7. 冲突处理

发生冲突时：

1. 执行 `git status` 查看冲突文件。
2. 在编辑器中打开冲突文件，保留正确内容并删除冲突标记。
3. 执行：

```powershell
git add .
git commit
```

如果 Git 返回的信息说明正在 `rebase`，应使用 `git rebase --continue`，不要直接创建普通提交。

## 8. 常用排查命令

```powershell
git status
git log --oneline --graph --decorate --all
git remote -v
git branch -a
git diff
git restore 文件名
```

- `git restore` 会丢弃未提交的文件修改，使用前请确认。
- 不要把密码、Token、私钥或 `.env` 文件提交到仓库。
