<html lang="en"><head>

        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- https://github.com/ -->
        <link href="https://github.githubassets.com/favicon.ico" rel="icon">

        <link crossorigin="anonymous" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" rel="stylesheet">

        <script crossorigin="anonymous" integrity="sha384-ZvpUoO/+PpLXR1lu4jmpXWu80pZlYUAfxl5NsBMWOEPSjUn/6Z/hRTt8+pR6L4N2" src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
        <script crossorigin="anonymous" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"></script>
        <script crossorigin="anonymous" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js"></script>
        <script src="https://unpkg.com/split.js@1.5.9/dist/split.min.js"></script>

        <script>
            // Allow buttons and form to render in Reset popover
            // https://getbootstrap.com/docs/4.5/getting-started/javascript/#sanitizer
            $.fn.tooltip.Constructor.Default.whiteList.button = [];
            $.fn.tooltip.Constructor.Default.whiteList.form = ['method'];

            // Current split
            let instance = null;

            // Destroy split
            function destroy() {
                if (instance) {
                    instance.destroy();
                    instance = null;
                }
            }

            // Splits UI horizontally or vertically
            function split() {

                // Unless nothing to split
                if ($('.split').length <= 1) {
                    return;
                }

                // https://nathancahill.github.io/Split.js/
                let options = {
                    gutterSize: 4,
                    onDragEnd: function() { // https://github.com/nathancahill/Split.js/issues/119
                        $('iframe').css('display', 'none').height();
                        $('iframe').css('display', 'block');
                    },
                    sizes: [40, 60]
                };

                // If desktop, per http://getbootstrap.com/docs/4.1/layout/overview/#responsive-breakpoints
                if ($(this).width() >= 768) {

                    // If not already horizontal
                    if (!$('.split:first').hasClass('split-horizontal')) {
                        destroy();
                        instance = Split(['.split:nth-of-type(1)', '.split:nth-of-type(2)'], $.extend(options, {cursor: 'col-resize', direction: 'horizontal'}));
                        $('.split').removeClass('split-vertical').addClass('split-horizontal');
                    }
                }

                // If not desktop
                else {

                    // If already horizontal
                    if (!$('.split:first').hasClass('split-vertical')) {
                        destroy();
                        instance = Split(['.split:nth-of-type(1)', '.split:nth-of-type(2)'], $.extend(options, {cursor: 'row-resize', direction: 'vertical'}));
                        $('.split').removeClass('split-horizontal').addClass('split-vertical');
                    }
                }
            }

            // DOMContentLoaded
            $(function() {

                // Split UI
                split();

                // Listen for resize
                $(window).on('resize', split);

                // Configure popovers
                $('*[data-toggle=popover]').popover({
                    html: true,
                    placement: 'bottom',
                    trigger: 'click'
                });

                // Listen for click on (dynamically created) reset button
                $(document).on('click', 'button[type=reset]', function() {
                    $('#reset').popover('hide');
                });

                // Dismiss popover if body (but not iframe or popover itself) clicked
                // https://jsfiddle.net/mattdlockyer/C5GBU/2/
                $('body').on('click', function (e) {
                    $('[data-toggle=popover]').each(function() {
                        if (!$(this).is(e.target) && $(this).has(e.target).length === 0 && $('.popover').has(e.target).length === 0) {
                            $(this).popover('hide');
                        }
                    });
                });

                // Dismiss popover if iframe clicked
                // http://www.jotform.org/jquery-codes/jquery-detect-click-outside-iframe/
                $(window).on('blur', function() {
                    $('*[data-toggle=popover]').popover('hide');
                });

            });

        </script>

        <style>

            /* Fill viewport */
            html, body {
                height: 100%;
            }
            iframe {
                border: 0;
                width: 100%;
            }

            /* Split horizontally or vertical */
            /* http://nathancahill.github.io/Split.js/ */
            .split {
                box-sizing: border-box;
                overflow: hidden;
            }
            .split.split-horizontal, .gutter.gutter-horizontal {
                height: 100%;
                float: left;
            }
            .split.split-vertical {}

            /* Match Codevolve's gutter */
            /* https://api.codevolve.com/assets/codevolve-5198bf1fcea7e01923fdbdaf53b4522a.css */
            .gutter {
                background-color: #3b4448;
            }

            /* Draw attention to gutter */
            .gutter.gutter-horizontal {
                cursor: col-resize;
            }
            .gutter.gutter-vertical {
                cursor: row-resize;
            }

            /* Grow to fill height */
            /* https://stackoverflow.com/a/45642449/5156190 */
            .flex-grow {
                flex: 1 0 auto;
            }

            /* Match Codevolve's terminal */
            nav {
                background-color: rgb(30, 35, 37);
            }

            /* Shorten nav */
            nav h4 {
                margin-bottom: 0;
            }

            /* Disable underline */
            nav h4 a:hover {
                text-decoration: none;
            }

            /* Scroll instructions on iOS */
            /* https://davidwalsh.name/scroll-iframes-ios */
            .flex-column {
                -webkit-overflow-scrolling: touch;
                overflow-y: scroll;
            }

            /* Ensure Codevolve's gear doesn't spin forever */
            iframe.flex-grow {
                min-height: 151px;
            }

            /* Fill height */
            iframe:not(.flex-grow) {
                height: 100%;
            }

        </style>

        <title>Caesar - CS50 Lab</title>
        

    </head>

    <body>

        
            <div class="split h-100 split-vertical" style="height: calc(40% - 2px);">
                <div class="d-flex flex-column h-100">
                    <iframe allowfullscreen="" src="/_site/8035e026c57ba9b9a06fc7d9fc83027028b132c8/caesar?"></iframe>
                </div>
            </div>
        

        <div class="gutter gutter-vertical" style="height: 4px;"></div><div class="split h-100 split-vertical" style="height: calc(60% - 2px);">
            <div class="d-flex flex-column h-100">
                <nav class="navbar navbar-dark">
                    <div>
                        <h4><a class="text-white" href="/">CS50 Lab</a></h4>
                        <span class="text-muted">Logged in as <strong>csbaxter</strong>. <a class="text-white" href="/logout">Log out</a>.</span>
                    </div>
                    <ul class="navbar-nav">
                        <button class="btn btn-outline-dark btn-sm" data-content="
                            <div class='mb-3'>Reset this lab to its initial state? Any changes you've made will be lost.</div>
                            <form class='form-inline' method='post'>
                                <button class='btn btn-danger btn-sm' type='submit'>Yes</button>
                                <button class='btn btn-link btn-sm text-dark' type='reset'>Cancel</button>
                            </form>
                            " data-placement="bottom" data-toggle="popover" data-trigger="click" id="reset" data-original-title="" title="">Reset</button>
                    </ul>
                </nav>
                <iframe allowfullscreen="" class="d-flex flex-column flex-grow" src="https://api.codevolve.com/api/v1/access_token/879313372E4CD30A0D472E93A91F7461"></iframe>
            </div>
        </div>
    


</body></html>
