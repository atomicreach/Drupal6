/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    var target;
    CKEDITOR.plugins.add('atomicengager', {
        //icons: 'abbr',
        init: function(editor) {
            // Plugin logic goes here...
            editor.addCommand("addToDic", {
                exec: function(editor)
                {
                    $.ajax({
                        'url': Drupal.settings.basePath + '?q=atomicengager/dictionary',
                        'type': 'POST',
                        'dataType': 'html',
                        'data': {word: target},
                        'success': function(data)
                        {
                         if (data == 'OK'){
                             alert('The word was added to the dictionary successfully. Please save the post and analyze it again to see the new results.');
                             $('#edit-body-wrapper div, #edit-body-wrapper iframe').contents().find(".highlight-sp:contains('"+target+"')").removeAttr("style").removeClass("highlight-sp");
                         }else{
                             alert("Error!! Someting Went Wrong. Code["+data+"]");
                         }   
                        },
                        'error': function(data)
                        {
                            alert("Error: " + data);

                        }
                    });
                }});

            var myCommand = {
                label: "Add to Dictionary",
                command: 'addToDic',
                group: 'image'
            };
            editor.contextMenu.addListener(function(element, selection) {
                if (element.$.attributes.class && element.$.attributes.class.value === "highlight-sp") {
                    target = element.$.firstChild.data;
                    return {
                        addToDic: CKEDITOR.TRISTATE_ON
                    };
                }
            });

            editor.addMenuItems({
                addToDic: {
                    label: "Add to Dictionary",
                    command: 'addToDic',
                    group: 'image',
                    order: 1
                }});

        }
    });
})(jQuery);