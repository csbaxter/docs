# Hello

## Getting Started

Head to <a href="http://ide.cs50.io" target=_blank>ide.cs50.io</a> and click “Log in” to access your CS50 IDE. Once your IDE loads, you should see that (by default) it’s divided into three parts. Toward the top of CS50 IDE is your “text editor”, where you’ll write all of your programs. Toward the bottom of is a “terminal window” (light blue, by default), a command-line interface (CLI) that allows you to explore your workspace’s files and directories, compile code, run programs, and even install new software. And on the left is your “file browser”, which shows you all of the files and folders currently in your IDE.

Start by clicking inside your terminal window. You should find that its “prompt” resembles the below.
```
~/ $
```
Click inside of that terminal window and then type
```
mkdir ~/pset1/
```
followed by Enter in order to make a directory (i.e., folder) called `pset1` inside of your home directory. Take care not to overlook the space between `mkdir` and `~/pset1` or any other character for that matter! Keep in mind that `~` always denotes your home directory and `~/pset1` denotes a directory called `pset1`, which is inside of `~`.

Here on out, to execute (i.e., run) a command means to type it into a terminal window and then hit Enter. Commands are “case-sensitive,” so be sure not to type in uppercase when you mean lowercase or vice versa.

Now execute
```
cd ~/pset1/
```
to move yourself into (i.e., open) that directory. Your prompt should now resemble the below.
```
~/pset1/ $
```
If not, retrace your steps and see if you can determine where you went wrong.

Now execute
```
mkdir ~/pset1/hello
```
to create a new directory called `hello` inside of your `pset1` directory. Then execute
```
cd ~/pset1/hello
```
to move yourself into that directory.

Shall we have you write your first program? From the File menu, click New File, and save it (as via the Save option in the File menu) as `hello.c` inside of your `~/pset1/hello` directory. Proceed to write your first program by typing precisely these lines into the file:

```
#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
}
```

Notice how CS50 IDE adds "syntax highlighting" (i.e., color) as you type, though CS50 IDE’s choice of colors might differ from this problem set’s. Those colors aren’t actually saved inside of the file itself; they’re just added by CS50 IDE to make certain syntax stand out. Had you not saved the file as `hello.c` from the start, CS50 IDE wouldn’t know (per the filename’s extension) that you’re writing C code, in which case those colors would be absent.

Do be sure that you type this program just right, else you’re about to experience your first bug! In particular, capitalization matters, so don’t accidentally capitalize words (unless they’re between those two quotes). And don’t overlook that one semicolon. C is quite nitpicky!

When done typing, select **File > Save** (or hit command- or control-s), but don’t quit. Recall that the red dot atop the tab should then disappear. Click anywhere in the terminal window beneath your code, and be sure that you’re inside of `~/workspace/pset1/hello/`. (Remember how? If not, type `cd` and then Enter, followed by `cd pset1/hello/` and then Enter.) Your prompt should be:

```
~/workspace/pset1/hello/ $
```

Let’s confirm that `hello.c` is indeed where it should be. Type

```
ls
```

followed by Enter, and you should see `hello.c`? If not, no worries; you probably just missed a small step. Best to restart these past several steps or ask for help!

Assuming you indeed see `hello.c`, let’s try to compile! Cross your fingers and then type

```
make hello
```

at the prompt, followed by Enter. (Well, maybe don’t cross your fingers whilst typing.) To be clear, type only `hello` here, not `hello.c`. If all that you see is another, identical prompt, that means it worked! Your source code has been translated to machine code (0s and 1s) that you can now execute. Type

```
./hello
```

at your prompt, followed by Enter, and you should see the below:

```
hello, world
```

And if you type

```
ls
```

followed by Enter, you should see a new file, `hello`, alongside `hello.c`. The first of those files, `hello`, should have an asterisk after its name that, in this context, means it’s "executable," a program that you can execute (i.e., run).

If, though, upon running `make`, you instead see some error(s), it’s time to debug! (If the terminal window’s too small to see everything, click and drag its top border upward to increase its height.) If you see an error like "expected declaration" or something just as mysterious, odds are you made a syntax error (i.e., typo) by omitting some character or adding something in the wrong place. Scour your code for any differences vis-à-vis the template above. It’s easy to miss the slightest of things when learning to program, so do compare your code against ours character by character; odds are the mistake(s) will jump out! Anytime you make changes to your own code, just remember to re-save via **File > Save** (or command- or control-s), then re-click inside of the terminal window, and then re-type

```
make hello
```

at your prompt, followed by Enter. (Just be sure that you are inside of `~/workspace/pset1/hello/` within your terminal window, as your prompt will confirm or deny.) If still seeing errors, try "prepending" `help50` to your command like this:

```
help50 make hello
```

That’ll pass the output of `make hello` to a program called `help50`, which CS50’s staff wrote. If `help50` recognizes your error message, it’ll offer some suggestions (in yellow). Just realize `help50` is new this year, so odds are it won’t recognize all error messages just yet!

Once you see no more errors, try "executing" (i.e., running) your program by typing

```
./hello
```

at your prompt, followed by Enter! Hopefully you now see whatever you told `printf` to print?

If not, reach out for help! Incidentally, if you find the terminal window too small for your tastes, know that you can open one in a bigger tab by clicking the circled plus (+) icon to the right of your `hello.c` tab.

## Walkthrough

## Usage

Your program should behave per the example below. Assumed that the underlined text is what some user has typed.

```
$ ./hello
hello, world
```

## Testing

### `check50`

To evaluate the correctness of your code, execute the below from inside `~/workspace/pset1/hello/`.

```
check50 cs50/2018/spring/hello
```

Assuming your program is correct, you should then see output like

```
:) hello.c exists
:) hello.c compiles
:) prints "hello, world\n"
```

where each green smiley means your program passed a check (i.e., test). You may also see a URL at the bottom of `check50`'s output, but that’s just for staff (though you’re welcome to visit it).

If you instead see yellow or red smileys, it means your code isn’t correct! For instance, suppose you instead see the below.

```
:( hello.c exists
  \ expected hello.c to exist
:| hello.c compiles
  \ can't check until a frown turns upside down
:| prints "Hello, world!\n"
  \ can't check until a frown turns upside down
```

Because `check50` doesn’t think `hello.c` exists, as per the red smiley, odds are you uploaded the wrong file or misnamed your file. The other smileys, meanwhile, are yellow because those checks are dependent on `hello.c` existing, and so they weren’t even run.

Suppose instead you see the below.

```
:) hello.c exists
:) hello.c compiles
:( prints "Hello, world!\n"
  \ expected output, but not "Hello, world!"
```

Odds are, in this case, you printed something other than `Hello, world!\n` verbatim, per the spec’s expectations. In particular, the above suggests you printed `Hello, world!`, without a trailing newline (`\n`).

Know that `check50` won’t actually record your scores in CS50’s gradebook. Rather, it lets you check your work’s correctness *before* you submit your work. Once you actually submit your work (per the directions at this spec’s end), CS50’s staff will use `check50` to evaluate your work’s correctness officially.

### `style50`

To evaluate the style of your code, execute the below from inside `~/workspace/pset1/hello/`.

```
style50 hello.c
```

If there’s room for improvement in your code’s style, highlighted in red will be any characters you should delete, and highlighted in green will be any characters you should add.

## Staff Solution

To run the staff’s implementation of `hello`, execute the below.

```
~cs50/pset1/hello
```

## Hints

Be sure to re-type (and not just copy and paste!) the code we’ve provided you above to get this program running. It’ll be good to develop this muscle memory starting now!
