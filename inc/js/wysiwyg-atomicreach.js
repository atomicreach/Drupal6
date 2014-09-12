Drupal.behaviors.atomicreachBehavior = function(context) {
    $(document).ajaxComplete(function(e, xhr, settings)
    {

        ARTabs();
        function ARTabs() {
            $('ul.AR-tabs').each(function() {
                console.log('inside each pwd');
                // For each set of tabs, we want to keep track of
                // which tab is active and it's associated content
                var $active, $content, $links = $(this).find('a');

                // If the location.hash matches one of the links, use that as the active tab.
                // If no match is found, use the first link as the initial active tab.
                $active = $($links.filter('[href="' + location.hash + '"]')[0] || $links[0]);
                $active.addClass('active');
                $content = $($active[0].hash);

                // Hide the remaining content
                $links.not($active).each(function() {
                    $(this.hash).hide();
                });

                // Bind the click event handler
                // delegatge is supported by jQuery 1.4
                // $(this).delegate('a', 'click', function (e) {
                $(this).contents().find('a').click(function(e) {
                    console.log('click pwd');
                    // Make the old tab inactive.
                    $active.removeClass('active');
                    $content.hide();

                    // Update the variables with the new link and content
                    $active = $(this);
                    $content = $(this.hash);

                    // Make the tab active.
                    $active.addClass('active');
                    $content.show();

                    // Prevent the anchor's default click action
                    e.preventDefault();
                });
            });
        }

        // Spelling Mistakes    
        $("#highlight-sp").toggle(function() {
            console.log("button clicked");
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(regexSm, {
                tagType: 'span',
                className: 'highlight-sp',
            });

            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red
            $(this).text("Clear Spelling Mistakes");
        }, function() {
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp").removeAttr("style")
            $(this).text('Spelling Mistakes');
        })

        $('#chksp').change(function() {
//            aSm = $("ul.spelling-mistakes li").find('span.smText').clone().not(":last").append("\\b|\\b").end().text();
//            var regexSm = new RegExp('(?:\\b|_)(' + aSm + ')(?:\\b|_)', 'ig');

            var words = $.map(SMwords, function(word, i) {
                return word.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
            });
            var regexSm = new RegExp('(\\b' + words.join("?[\\x27]?[\\S]+\\b|\\b") + '?[\\x27]?[\\S]+\\b)', 'ig');
//        console.log(regexSm);




//console.log("spelling button clicked");
            if ($(this).is(":checked")) {
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(regexSm, {
                    tagType: 'span',
                    className: 'highlight-sp',
                });

                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red

            } else {

                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp").removeAttr("style")

            }
        });

        $('#chkso').change(function() {

            if ($(this).is(":checked")) {
                text_paragraphs = $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(domExpression);

                $.each(paragraphs, function(index, value) {
                    if (value == 'HIT' || value == 'UNAVAILABLE')
                        return;
                    type = (value == 'TOO SIMPLE') ? 'too-simple' : 'too-complex';
                    $(text_paragraphs[index]).wrapInner("<span class='highlight-so " + type + "'></span>");
                });
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".too-simple").css("background", tooSimpleColor);
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".too-complex").css("background", tooComplexColor);

            } else {

                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-so").removeAttr("style")

            }
        });

        // Grammar Mistakes    
        var words = $.map(GMwords, function(word, i) {
            return word.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
        });
        var regexGm = new RegExp('(\\b' + words.join("?[\\x27]?[\\S]+\\b|\\b") + '?[\\x27]?[\\S]+\\b)', 'g');

        $("#highlight-gm").toggle(function() {
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(regexGm, {
                tagType: 'span',
                className: 'highlight-grm',
            });

            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green
            $(this).text("Clear Grammar Mistakes");
        }, function() {

            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");
            $(this).text('Grammar Mistakes');
        })



        $('#chkgm').change(function() {

            if ($(this).is(":checked")) {
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(regexGm, {
                    tagType: 'span',
                    className: 'highlight-grm',
                });

                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green


            } else {
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");

            }
        });

        // Invalid Lunks    
        aIl = $("ul.invalid-links li").find('span.ilText').clone().not(":last").append("|").end().text();

        // aIl = / www.atomicreach.coms | http:\/\/www.atomicreach.comsi\/ewruu /ig

        var linkArray = aIl.split('|');

        /*var regexIl = new RegExp(aIl,'gi');*/

        $("#highlight-il").toggle(function() {

            /* 
             $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(regexIl, {
             tagType:   'span',
             className: 'highlight-il',
             });  
             $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-il").css("border-bottom", "2px solid orange");
             */


            $.each(linkArray, function(index, value) {
                vlink = "[href='" + value + "']";
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
            });


            $(this).text("Clear Underperforming Link");
        }, function() {
            // $("#edit-body-wrapper iframe").contents().find('body').find('style').remove(); 
            // $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex();
            // $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-il").css("border-bottom", "");

            /*  $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-il").removeAttr("style"); */

            $.each(linkArray, function(index, value) {
                vlink = "[href='" + value + "']";
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(vlink).removeAttr("style");
            });

            $(this).text('Underperforming Link');
        })



        $('#chkul').change(function() {

            if ($(this).is(":checked")) {

                $.each(linkArray, function(index, value) {
                    vlink = "[href='" + value + "']";

                    $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
                });


            } else {

                $.each(linkArray, function(index, value) {
                    vlink = "[href='" + value + "']";
                    $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(vlink).removeAttr("style");
                });

            }
        });


        /*--------Paragraph Density--------------*/
        $("#chkpwd").change(function() {
            perParagraphHighlight(this, 'TOOSHORT', 'TOOLONG', PWDtooShortColor, PWDtooLongColor, PWDdomExpression, PWDparagraphs, 'pwd');
        });

        function perParagraphHighlight(element, stateA, stateB, colorA, colorB, domExpression, dataToHighlight, dimension)
        {
            if ($(element).is(":checked")) {
                stateLabelA = stateA.toLowerCase().replace(' ', '-');
                stateLabelB = stateB.toLowerCase().replace(' ', '-');
                text_paragraphs = $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(domExpression);
                $.each(dataToHighlight, function(index, value) {
                    if (value == 'HIT' || value == 'UNAVAILABLE' || value == '' || value == 'length_hit')
                        return;
                    type = (value == stateLabelA) ? stateLabelA : stateLabelB;
                    $(text_paragraphs[index]).wrapInner("<span class='highlight-" + dimension + " " + type + "'></span>");
                });
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find("." + stateLabelA).css("background", colorA);
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find("." + stateLabelB).css("background", colorB);
            } else {
//            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-"+dimension).contents().unwrap();
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-" + dimension).removeAttr("style");
            }
        }
        ;



        // clear highlight before submiting form, this way will clean the html added to the iframe
        $('#node-form').submit(function() {


            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp").removeAttr("style");
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(undefined, {
                tagType: 'span',
                className: 'highlight-sp',
            });

            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().highlightRegex(undefined, {
                tagType: 'span',
                className: 'highlight-grm',
            });

            $.each(linkArray, function(index, value) {
                vlink = "[href='" + value + "']";
                $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(vlink).removeAttr("style");
            });
            $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-so").contents().unwrap();
            return true;
        });

//});
//var basePath = Drupal.settings.atomicreach.basePath;
        CustomDictionary = {
            add: function(w) {
                return jQuery.ajax({
                    //url : 'sites/all/modules/atomicreach/inc/customDictionary.php',
                    data: {action: 'ar_custom_dictionary', word: w},
                    async: false
                }).responseText == 'OK';
            }
        }
    });//ajax complete
}