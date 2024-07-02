[![wakatime](https://wakatime.com/badge/github/langningchen/OJTool.svg)](https://wakatime.com/badge/github/langningchen/OJTool)

# OJTool

## Introduction

Get problem and submit code for OJ just from your CLI! 

## Usage

- (Optional) If you want to predict Luogu captcha by AI module, install python package `numpy`, `tensorflow`, `pillow`, `pandas`, `matplotlib`

1. Clone this repository
2. Run `./Run.sh` to build the project
3. Run `./Build/OJTool` to run program

or

1. Download the executable file from GitHub Actions artifact
2. Run `./Build/OJTool` to run program

## Params

| Param name | Full name      |
| :--------- | :------------- |
| `-oj`      | `--oj`         |
| `-u`       | `--username`   |
| `-p`       | `--password`   |
| `-o`       | `--operation`  |
| `-pr`      | `--problem-id` |

| OJ           | Available operation                                         | Website                   | Visibility |
| :----------- | :---------------------------------------------------------- | :------------------------ | :--------- |
| `Luogu`      | `GetProblemDetail`,`SubmitCode`,`GetAnswerOrTips`,`ClockIn` | https://www.luogu.com.cn/ | Public     |
| `Etiger`     | `GetProblemDetail`,`SubmitCode`,`GetAnswerOrTips`,`ClockIn` | https://www.etiger.vip/   | Private    |
| `XMOJ`       | `GetProblemDetail`,`SubmitCode`                             | https://www.xmoj.tech/    | Private    |
| `USACO`      | `GetProblemDetail`,`SubmitCode`                             | https://usaco.org/        | Public     |
| `UVa`        | `GetProblemDetail`,`SubmitCode`                             | https://onlinejudge.org/  | Public     |
| `Codeforces` | `GetProblemDetail`,`SubmitCode`                             | https://codeforces.com/   | Public     |
| `AtCoder`    | `GetProblemDetail`,`SubmitCode`                             | https://atcoder.jp/       | Public     |

## License

This project is licensed under the terms of the GNU General Public License v3.0.