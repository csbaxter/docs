
<!DOCTYPE html>

<!-- https://ben.balter.com/jekyll-style-guide/themes/ -->

<html lang="en-US">

    <head>

        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <!-- https://cdnjs.com/libraries/Primer -->
        <link href="https://cdnjs.cloudflare.com/ajax/libs/Primer/10.8.1/build.css" rel="stylesheet">

        <link href="https://cdn.jsdelivr.net/npm/pygments-rouge-css@0.1.0/github.css" rel="stylesheet">

        <link href="https://cdnjs.cloudflare.com/ajax/libs/octicons/8.0.0/build.css" rel="stylesheet">

        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>

        <!-- https://www.bryanbraun.com/anchorjs/ -->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/anchor-js/4.1.1/anchor.min.js"></script>

        <!-- http://fitvidsjs.com/ -->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/fitvids/1.2.0/jquery.fitvids.min.js"></script>

        <!-- https://github.com/harttle/liquidjs --> 
        <script src="https://unpkg.com/liquidjs/dist/liquid.min.js"></script>

        <!-- https://github.com/markdown-it/markdown-it -->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/markdown-it/8.4.2/markdown-it.min.js"></script>

        <script>

            $(function() {

                // Add support for tasklist
                // https://github.com/github/cmark/issues/23
                let html = $('body').html();
                html = html.replace(/<li>\[ \]\s+/gm, '<li class="task-list-item"><input class="task-list-item-checkbox" disabled type="checkbox"> ');
                html = html.replace(/<li>\[x\]\s+/gm, '<li class="task-list-item"><input checked class="task-list-item-checkbox" disabled type="checkbox"> ');
                $('body').html(html);

                // Add anchors to headings
                anchors.add();

                // Enable deep-linking
                $('.anchorjs-link').click(function() {
                    let hash = $(this).attr('href');
                    if (window.parent.location.hash === hash) { // In case user scrolled then re-clicked same anchor
                        $(window.parent).trigger('hashchange');
                    }
                    else {
                        window.parent.location.hash = hash;
                    }
                    return false;
                });

                // Next
                $('[data-next]').each(function(index) {

                    // Hide next elements
                    next($(this)).addClass('next');

                    // Listen for clicks
                    $(this).click(function() {

                        // Show next elements
                        next($(this)).removeClass('next');

                        // Remember button's offset
                        let top = $(this).offset().top;
                        let bottom = top + $(this).outerHeight(true);

                        // Scroll to next elements
                        scroll(bottom + 1);

                        // Disable button
                        $(this).prop('disabled', true).addClass('disabled');
                    });
                });

                // Check
                $('[data-check]').each(function() {

                    // Parse popover
                    let check = $(this).find('> p > button').first();
                    let template = $(this).find('> script').first();
                    let message = $(this).find('> .Popover-message').first();
                    let results = $(this).find('> .Popover-message > div').first();
                    let recheck = $(this).find('> .Popover-message > button').first();

                    // Listen for clicks
                    check.click(function() {

                        // If closing
                        if ($(this).hasClass('selected')) {

                            // Close popover
                            message.addClass('d-none');
                            check.removeClass('selected');
                        }

                        // If opening
                        else {

                            // Open popover
                            message.removeClass('d-none');
                            check.addClass('selected');

                            // Disable rechecking
                            //recheck.html('Checking...');
                            //recheck.prop('disabled', true);

                            // TODO: associate below with a function so recheck can call it

                            // 
                            results.html('Checking...');

                            // POST /check
                            $.post('https://lab.cs50.io/csbaxter/nestlabs/2020/caesar/?check', {
                                template: template.text()
                            }, 'post')
                            .done(function(data, textStatus, jqXHR) {
                                results.html(data);
                            })
                            .fail(function(jqXHR, textStatus, errorThrown) {
                                results.html(errorThrown);
                            })
                            .always(function() {

                                // Enable rechecking
                                //recheck.html('Recheck');
                                //recheck.prop('disabled', false);
                            });
                        }
                    });
                });

                // Spoiler
                $('[data-spoiler]').each(function() {
                    let button = $(this).find('> p > button').first();
                    let message = $(this).find('> .Popover-message').first();
                    button.click(function() {
                        message.toggleClass('d-none');
                        button.toggleClass('selected');
                    });
                });

                // Add padding between emojis and text nodes
                $('button').contents().filter(function() {
                    return this.nodeType === Node.TEXT_NODE;
                }).wrap('<span></span>');
                $('button span').each(function() {
                    $(this).html($(this).html().trim());
                    if (!$(this).html()) {
                        $(this).remove();
                    }
                });

                // Listen for hashchange
                $(window.parent).on('hashchange', function() {

                    // Find heading
                    let id = window.parent.location.hash.slice(1);
                    if (!id) {
                        return false;
                    }
                    let heading = $('#' + id);
                    if (!heading.length) {
                        return false;
                    }

                    // Elements through this heading
                    previous(heading).removeClass('next').find('[data-next]').remove();

                    // Elements after this heading through next button
                    next(heading).removeClass('next');

                    // Scroll to heading
                    let top = heading.offset().top - parseInt(heading.css('marginTop')) + 1;
                    scroll(top);
                    return false;
                });
                $(window.parent).trigger('hashchange');

                // Embed videos responsively
                $('iframe[data-video]').parent().fitVids();

                // Mimic paragraphs
                $('iframe[data-video]').parent().addClass('my-3');

                // Make site visible
                $('body').removeClass('v-hidden');
            });

            // Previous slice(s) of elements
            function previous(element) {

                // All elements, in document order
                let elements = $('body *');

                // Elements through this one
                let end = elements.index($(element)) + 1;
                return elements.slice(0, end);
            }

            // Next slice of elements
            function next(element) {

                // All elements, in document order
                let elements = $('body *');

                // First element after this element
                let start = elements.index(element) + 1;

                // Following buttons
                let buttons = elements.slice(start).find('[data-next]');

                // Last element before next button
                let end = (buttons.length > 0) ? elements.index(buttons[0]) : elements.length;

                // Next slice
                return elements.slice(start, end);
            }

            // Scroll to y
            function scroll(y) {

                // Margin required to scroll to top of viewport
                let margin = Math.floor($(window).height() - ($('body').outerHeight() - y));
                $('body').css('margin-bottom', Math.ceil(margin) + 'px');

                // Scroll to next elements
                $('html, body').animate({scrollTop: y}, 500);
            }

        </script>

        <style>

            /* Disable default borders */
            iframe {
                border: 0;
                box-sizing: content-box;
            }

            /* Match headings */
            .anchorjs-link {
                color: inherit;
            }
            .anchorjs-link:hover {
                text-decoration: none;
            }

            /* Align emoji with surrounding text better */
            .markdown-body .emoji {
                vertical-align: bottom;
            }

            /* Separate emoji from text by 1 character */
            button *:not(:last-child) {
                margin-right: 1ch;
            }

            /* Left-align buttons' text */
            .btn-block {
                text-align: left;
            }

            .next {
                display: none;
            }

            /* Else increases button's height */
            .Popover button p:last-child {
                margin-bottom: 0;
            }

            /* Else of fixed size */
            .Popover-message {
                width: inherit;
            }

            /* Remain aligned with body */
            .Popover-message--top-left {
                left: inherit;
            }

            .Popover-message .Box {
                margin-bottom: 10px; /* TODO: match <p>'s margin-bottom via Sass */
            }

            /* Match bg-blue-light */
            .Popover-message.bg-blue-light button:not(:hover),
            .Popover-message.bg-blue-light button.Box-btn-octicon,
            .Popover-message.bg-blue-light .Box {
                background-color: #f1f8ff;
            }
            .Popover-message.bg-blue-light::after {
                border-bottom-color: #f1f8ff;
            }

            /* Match bg-gray-light */
            .Popover-message.bg-gray-light::after {
                border-bottom-color: #fafbfc;
            }

            /* Match bg-green-light */
            .Popover-message.bg-green-light button:not(:hover) {
                background-color: #dcffe4;
            }
            .Popover-message.bg-green-light::after {
                border-bottom-color: #dcffe4;
            }

            /* Strip trailing whitespace from popovers */
            .Popover-message > :last-child {
                margin-bottom: 0;
            }

            /* From GitHub's own task-lists.scss, per Chrome DevTools */
            .task-list-item {
                list-style-type: none;
            }
            .task-list-item-checkbox {
                margin: 0 0.2em 0.25em -1.6em;
                vertical-align: middle;
            }

        </style>

        <title>Caesar</title>

    </head>

    <body class="markdown-body p-3 v-hidden">

        <h1 id="caesar">Caesar</h1>

<iframe allowfullscreen="" class="border" data-video="" height="315" src="https://www.youtube.com/embed/Rg8P1wHDc0s?rel=0&amp;showinfo=0" width="560"></iframe>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="et-tu">Et tu?</h2>

<p>Supposedly, Caesar (yes, that Caesar) used to “encrypt” (i.e., conceal in a reversible way) confidential messages by shifting each letter therein by some number of places. For instance, he might write A as B, B as C, C as D, …, and, wrapping around alphabetically, Z as A. And so, to say HELLO to someone, Caesar might write IFMMP. Upon receiving such messages from Caesar, recipients would have to “decrypt” them by shifting letters in the opposite direction by the same number of places.</p>

<p>The secrecy of this “cryptosystem” relied on only Caesar and the recipients knowing a secret, the number of places by which Caesar had shifted his letters (e.g., 1). Not particularly secure by modern standards, but, hey, if you’re perhaps the first in the world to do it, pretty secure!</p>

<p>Unencrypted text is generally called <em>plaintext</em>. Encrypted text is generally called <em>ciphertext</em>. And the secret used is called a <em>key</em>.</p>

<p>To be clear, then, here’s how encrypting <code class="language-plaintext highlighter-rouge">HELLO</code> with a key of 1 yields <code class="language-plaintext highlighter-rouge">IFMMP</code>:</p>

<table>
  <thead>
    <tr>
      <th>plaintext</th>
      <th>H</th>
      <th>E</th>
      <th>L</th>
      <th>L</th>
      <th>O</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>+ key</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
      <td>1</td>
    </tr>
    <tr>
      <td>= ciphertext</td>
      <td>I</td>
      <td>F</td>
      <td>M</td>
      <td>M</td>
      <td>P</td>
    </tr>
  </tbody>
</table>

<p>More formally, Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by <em>k</em> positions. More formally, if <em>p</em> is some plaintext (i.e., an unencrypted message), <em>p<sub>i</sub></em> is the <em>i<sup>th</sup></em> character in <em>p</em>, and <em>k</em> is a secret key (i.e., a non-negative integer), then each letter, <em>c<sub>i</sub></em>, in the ciphertext, <em>c</em>, is computed as</p>

<p>c<sub>i</sub> = (p<sub>i</sub> + k) % 26</p>

<p>wherein <code class="language-plaintext highlighter-rouge">% 26</code> here means “remainder when dividing by 26.” This formula perhaps makes the cipher seem more complicated than it is, but it’s really just a concise way of expressing the algorithm precisely. Indeed, for the sake of discussion, think of A (or a) as 0, B (or b) as 1, …, H (or h) as 7, I (or i) as 8, …, and Z (or z) as 25. Suppose that Caesar just wants to say Hi to someone confidentially using, this time, a key, <em>k</em>, of 3. And so his plaintext, <em>p</em>, is Hi, in which case his plaintext’s first character, <em>p<sub>0</sub></em>, is H (aka 7), and his plaintext’s second character, <em>p<sub>1</sub></em>, is i (aka 8). His ciphertext’s first character, <em>c<sub>0</sub></em>, is thus K, and his ciphertext’s second character, <em>c<sub>1</sub></em>, is thus L. Can you see why?</p>

<p>Let’s write a program called <code class="language-plaintext highlighter-rouge">caesar</code> that enables you to encrypt messages using Caesar’s cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime. We shouldn’t necessarily assume that the user’s key is going to be a number; though you may assume that, if it is a number, it will be a positive integer.</p>

<p>Here are a few examples of how the program might work. For example, if the user inputs a key of <code class="language-plaintext highlighter-rouge">1</code> and a plaintext of <code class="language-plaintext highlighter-rouge">HELLO</code>:</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP
</code></pre></div></div>

<p>Here’s how the program might work if the user provides a key of <code class="language-plaintext highlighter-rouge">13</code> and a plaintext of <code class="language-plaintext highlighter-rouge">hello, world</code>:</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 13
plaintext:  hello, world
ciphertext: uryyb, jbeyq
</code></pre></div></div>

<p>Notice that neither the comma nor the space were “shifted” by the cipher. Only rotate alphabetical characters!</p>

<p>How about one more? Here’s how the program might work if the user provides a key of <code class="language-plaintext highlighter-rouge">13</code> again, with a more complex plaintext:</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 13
plaintext:  be sure to drink your Ovaltine
ciphertext: or fher gb qevax lbhe Binygvar
</code></pre></div></div>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Why? 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<iframe allowfullscreen="" class="border" data-video="" height="315" src="https://www.youtube.com/embed/9K4FsAHB-C8?rel=0&amp;showinfo=0" width="560"></iframe>


</div>
</div>

<p>Notice that the case of the original message has been preserved. Lowercase letters remain lowercase, and uppercase letters remain uppercase.</p>

<p>And what if a user doesn’t cooperate?</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar
Usage: ./caesar key
</code></pre></div></div>

<p>Or really doesn’t cooperate?</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 1 2 3
Usage: ./caesar key
</code></pre></div></div>

<p>How to begin? Let’s approach this problem one step at a time.</p>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="pseudocode">Pseudocode</h2>

<p>First, write in <code class="language-plaintext highlighter-rouge">pseudocode.txt</code> at right some pseudocode that implements this program, even if not (yet!) sure how to write it in code. There’s no one right way to write pseudocode, but short English sentences suffice. Recall how we wrote pseudocode for <a href="https://cdn.cs50.net/2018/fall/lectures/0/lecture0.pdf" target="_blank">finding Mike Smith</a>. Odds are your pseudocode will use (or imply using!) one or more functions, conditions, Boolean expressions, loops, and/or variables.</p>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Spoiler 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<p>There’s more than one way to do this, so here’s just one!</p>

<ol>
  <li>Check that program was run with one command-line argument</li>
  <li>Convert that command-line argument from a <code class="language-plaintext highlighter-rouge">string</code> to an <code class="language-plaintext highlighter-rouge">int</code>
</li>
  <li>Prompt user for plaintext</li>
  <li>Iterate over each character of the plaintext:
    <ol>
      <li>If it is an uppercase letter, rotate it, preserving case, then print out the rotated character</li>
      <li>If it is a lowercase letter, shift it, preserving case, then print out the rotated character</li>
      <li>If it is neither, print out the character as is</li>
    </ol>
  </li>
  <li>Print a newline</li>
</ol>

<p>It’s okay to edit your own after seeing this pseudocode here, but don’t simply copy/paste ours into your own!</p>


</div>
</div>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="counting-command-line-arguments">Counting Command-Line Arguments</h2>

<p>Whatever your pseudocode, let’s first write only the C code that checks whether the program was run with a single command-line argument before adding additional functionality.</p>

<p>Specifically, modify <code class="language-plaintext highlighter-rouge">caesar.c</code> at right in such a way that: if the user provides exactly one command-line argument, it prints <code class="language-plaintext highlighter-rouge">Success</code>; if the user provides no command-line arguments, or two or more, it prints <code class="language-plaintext highlighter-rouge">Usage: ./caesar key</code>. Remember, since this key is coming from the command line at runtime, and not via <code class="language-plaintext highlighter-rouge">get_string</code>, we don’t have an opportunity to re-prompt the user. The behavior of the resulting program should be like the below.</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 20
Success
</code></pre></div></div>

<p>or</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar
Usage: ./caesar key
</code></pre></div></div>

<p>or</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 1 2 3
Usage: ./caesar key
</code></pre></div></div>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Hints 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<ul>
  <li>Recall that you can compile your program with <code class="language-plaintext highlighter-rouge">make</code>.</li>
  <li>Recall that you can print with <code class="language-plaintext highlighter-rouge">printf</code>.</li>
  <li>Recall that <code class="language-plaintext highlighter-rouge">argc</code> and <code class="language-plaintext highlighter-rouge">argv</code> give you information about what was provided at the command line.</li>
  <li>Recall that the name of the program itself (here, <code class="language-plaintext highlighter-rouge">./caesar</code>) is in <code class="language-plaintext highlighter-rouge">argv[0]</code>.</li>
</ul>


</div>
</div>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="accessing-the-key">Accessing the Key</h2>

<p>Now that your program is (hopefully!) accepting input as prescribed, it’s time for another step.</p>

<p>You can assume that, if a user does provide a command-line argument, it will be a non-negative integer (e.g., 1). No need to check that it’s indeed numeric. But remember, you should convert that string (recall that <code class="language-plaintext highlighter-rouge">argv</code> is an array of strings, even if those strings happen to look like numbers) to an actual integer. There is a function you’ve used before (remember <code class="language-plaintext highlighter-rouge">atoi</code>?) that can do this for you!</p>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Hints 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<ul>
  <li>Recall that <code class="language-plaintext highlighter-rouge">argc</code> and <code class="language-plaintext highlighter-rouge">argv</code> give you information about what was provided at the command line.</li>
  <li>Recall that <code class="language-plaintext highlighter-rouge">argv</code> is an array of strings.</li>
  <li>Recall that computer scientists like counting starting from 0.</li>
  <li>Recall that we can access individual elements of an array, such as <code class="language-plaintext highlighter-rouge">argv</code> using square brackets, for example: <code class="language-plaintext highlighter-rouge">argv[0]</code>.</li>
  <li>Recall that the <code class="language-plaintext highlighter-rouge">atoi</code> function converts a string that looks like a number into that number.</li>
</ul>


</div>
</div>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="peeking-underneath-the-hood">Peeking Underneath the Hood</h2>

<p>As human beings it’s easy for us to intuitively understand the formula described above, inasmuch as we can say “H + 1 = I”. But can a computer understand that same logic? Let’s find out. For now, we’re going to temporarily ignore the key the user provided and instead prompt the user for a secret message and attempt to shift all of its characters by just 1.</p>

<p>Extend the functionality of <code class="language-plaintext highlighter-rouge">caesar.c</code> at right such that, after accessing the key, we prompt the user for a string and then shift all of its characters by 1, printing out the result. We can also at this point probably remove the line of code we wrote earlier that prints <code class="language-plaintext highlighter-rouge">Success</code>. All told, this might result in this behavior:</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./caesar 1
plaintext:  hello
ciphertext: ifmmp
</code></pre></div></div>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Hints 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<ul>
  <li>Try to iterate over every character in the plaintext and literally add 1 to it, then print it.</li>
  <li>If <code class="language-plaintext highlighter-rouge">c</code> is a variable of type <code class="language-plaintext highlighter-rouge">char</code> in C, what happens when you call <code class="language-plaintext highlighter-rouge">printf("%c", c + 1)</code>?</li>
</ul>


</div>
</div>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="your-turn">Your Turn</h2>

<p>Now it’s time to tie everything together! Instead of shifting the characters by 1, modify <code class="language-plaintext highlighter-rouge">caesar.c</code> to instead shift them by the actual key value. And be sure to preserve case! Uppercase letters should stay uppercase, lowercase letters should stay lowercase, and characters that aren’t alphabetical should remain unchanged.</p>

<div class="Popover position-relative my-3" data-spoiler="">
<p><button class="btn"> Hints 
</button></p>
<div class="Popover-message Popover-message--top-left p-4 Box box-shadow-extra-large bg-gray-light d-none">

<ul>
  <li>Best to use the modulo (i.e., remainder) operator, <code class="language-plaintext highlighter-rouge">%</code>, to handle wraparound from Z to A! But how?</li>
  <li>Things get weird if we try to wrap <code class="language-plaintext highlighter-rouge">Z</code> or <code class="language-plaintext highlighter-rouge">z</code> by 1 using the technique in the previous section.</li>
  <li>Things get weird also if we try to wrap punctuation marks using that technique.</li>
  <li>Recall that ASCII maps all printable characters to numbers.</li>
  <li>Recall that the ASCII value of <code class="language-plaintext highlighter-rouge">A</code> is 65. The ASCII value of <code class="language-plaintext highlighter-rouge">a</code>, meanwhile, is 97.</li>
  <li>If you’re not seeing any output at all when you call <code class="language-plaintext highlighter-rouge">printf</code>, odds are it’s because you’re printing characters outside of the valid ASCII range from 0 to 127. Try printing characters as numbers (using <code class="language-plaintext highlighter-rouge">%i</code> instead of <code class="language-plaintext highlighter-rouge">%c</code>) at first to see what values you’re printing, and make sure you’re only ever trying to print valid characters!</li>
</ul>


</div>
</div>

<p><button class="btn btn-primary" data-next="" type="button"> Next 
</button></p>

<h2 id="testing">Testing</h2>

<h3 id="correctness">Correctness</h3>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>check50 cs50/problems/2019/ap/caesar
</code></pre></div></div>

<h3 id="style">Style</h3>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>style50 caesar.c
</code></pre></div></div>

<h2 id="how-to-submit">How to Submit</h2>

<p>Execute the below, logging in with your GitHub username and password when prompted. For security, you’ll see asterisks (<code class="language-plaintext highlighter-rouge">*</code>) instead of the actual characters in your password.</p>

<div class="language-plaintext highlighter-rouge"><div class="highlight"><pre class="highlight"><code>submit50 cs50/problems/2019/ap/caesar
</code></pre></div></div>


    </body>

</html>
