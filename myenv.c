/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif
extern char **environ;

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (putenv(argv[i]) < 0) {
            execvp(argv[i], &argv[i]);
            perror(argv[i]);
            return 1;
        }
    }
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    return 0;
}

/* 実行例
% make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c
//コンパイルエラーなし

・環境変数の変更
% ./myenv LC_TIME=en_US.UTF-8 date
Wed Jul  1 09:10:12 JST 2026

・複数の環境変数の変更
 % ./myenv LC_TIME=ja_JP.UTF-8 TZ=Cuba date
2026年 6月30日 火曜日 19時55分53秒 CDT

・引数付きのコマンドの場合
% ./myenv LC_TIME=ru_RU.UTF-8 ls -l
total 384
-rw-r--r--  1 fukamachiharukahitoshi  staff     132 30 июня  10:41 Makefile
-rwxr-xr-x  1 fukamachiharukahitoshi  staff   33688 30 июня  11:58 myenv
-rw-r--r--  1 fukamachiharukahitoshi  staff     600 30 июня  11:58 myenv.c
-rwxr-xr-x  1 fukamachiharukahitoshi  staff     216 30 июня  10:41 myputenv.c
-rw-r--r--  1 fukamachiharukahitoshi  staff      93 30 июня  10:41 myputenv.h
-rw-r--r--  1 fukamachiharukahitoshi  staff    1268 30 июня  10:41 README.md
-rw-r--r--  1 fukamachiharukahitoshi  staff  139098 30 июня  10:41 README.pdf

・コマンドを省略した場合
 % ./myenv LC_TIME=en_US.UTF-8
__CFBundleIdentifier=com.apple.Terminal
TMPDIR=/var/folders/qy/1yrl929n72gctqjr1yyxhpvm0000gn/T/
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.Vg6kXCWQBU/Listeners
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=466
TERM_SESSION_ID=FEF06148-083B-47B5-A184-95EDB754A26D
SHELL=/bin/zsh
HOME=/Users/fukamachiharukahitoshi
LOGNAME=fukamachiharukahitoshi
USER=fukamachiharukahitoshi
PATH=/opt/homebrew/opt/openjdk/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/opt/pmk/env/global/bin:/opt/homebrew/bin
SHLVL=1
PWD=/Users/fukamachiharukahitoshi/desktop/Syspro2/kadai09-i23fukamati
OLDPWD=/Users/fukamachiharukahitoshi/desktop/Syspro2
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/fukamachiharukahitoshi/desktop/Syspro2/kadai09-i23fukamati/./myenv
LC_TIME=en_US.UTF-8

・存在しないコマンドの場合
% ./myenv aaa
aaa: No such file or directory

*/
