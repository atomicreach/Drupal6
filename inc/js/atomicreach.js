jQuery(document).ready(function($) {
    // Sort result(Red first, Green last)
//    $('div.ac-container div').tsort({attr:'class'});
    
    
 
   // Spelling Mistakes    
   aSm = $("ul.spelling-mistakes li").find('span.smText').clone().not(":last").append("\\b|\\b").end().text();
   var regexSm = new RegExp('(?:\\b|_)(' + aSm + ')(?:\\b|_)','ig');
//     var regexSm = new RegExp('\\b' + aSm + '\\b','ig');
  
   console.log(regexSm);
   console.log ("asm: "+aSm);
   
   // var regexSm = /\bstandin\b|\bfondue|\bblog\b|\bPratik\b|\bblog\b/ig;
   
   $("#highlight-sp").toggle(function(){        
     $('.preview').contents().highlightRegex(regexSm, {
      tagType:   'span',
      className: 'highlight-sp',
      });
      
     $('.preview').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red
     $(this).text("Clear Spelling Mistakes");
   }, function(){
     // $(".preview").contents().find('body').find('style').remove(); 
     // $('.preview').contents().highlightRegex();
     // $('.preview').contents().find(".highlight-sp").css("border-bottom", "");
     $('.preview').contents().find(".highlight-sp").removeAttr("style")     
     $(this).text('Spelling Mistakes');
   }) 
   
   
   
  $('#chksp').change(function() {
    
      if($(this).is(":checked")) {

         $('.preview').contents().highlightRegex(regexSm, {
          tagType:   'span',
          className: 'highlight-sp',
          });
          
        //  console.log(regexSm); 
          
         $('.preview').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red
          
      }else{
        
         $('.preview').contents().find(".highlight-sp").removeAttr("style")     
          
      }
  });

  $('#chkso').change(function() {
      
      if($(this).is(":checked")) {
        var paragraphs = $(this).data('paragraphs');
        var domExpression = $(this).data('domExpression');
        var tooSimpleColor = $(this).data('tooSimpleColor');
        var tooComplexColor = $(this).data('tooComplexColor');

        text_paragraphs = $('.preview').contents().find(domExpression);
        $.each(paragraphs, function(index, value) {
       if (value == 'HIT' || value == 'UNAVAILABLE')
            return;
          type = (value == 'TOO SIMPLE')?'too-simple':'too-complex';
          $(text_paragraphs[index]).wrapInner("<span class='highlight-so "+type+"'></span>");
        });
          
        //  console.log(regexSm); 
          
         $('.preview').contents().find(".too-simple").css("background", tooSimpleColor);
         $('.preview').contents().find(".too-complex").css("background", tooComplexColor);
          
      }else{
        
         $('.preview').contents().find(".highlight-so").removeAttr("style")     
          
      }
  });  
   
   
   
   
   

   // Grammar Mistakes    
   aGm = $("ul.grammar-mistakes li").find('span.gmText').clone().not(":last").append("|").end().text();
   var regexGm = new RegExp(aGm,'gi');

   $("#highlight-gm").toggle(function(){        
     $('.preview').contents().highlightRegex(regexGm, {
      tagType:   'span',
      className: 'highlight-grm',
      });
    
     $('.preview').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green
     $(this).text("Clear Grammar Mistakes");
   }, function(){
     // $(".preview").contents().find('body').find('style').remove(); 
     // $('.preview').contents().highlightRegex();
     // $('.preview').contents().find(".highlight-grm").css("border-bottom", "");
     
     $('.preview').contents().find(".highlight-grm").removeAttr("style");    
     $(this).text('Grammar Mistakes');
   }) 
   
   
  
  $('#chkgm').change(function() {
    
      if($(this).is(":checked")) {
         $('.preview').contents().highlightRegex(regexGm, {
          tagType:   'span',
          className: 'highlight-grm',
          });
        
         $('.preview').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green

          
      }else{
         $('.preview').contents().find(".highlight-grm").removeAttr("style");    
    
      }
  });    
   
   
   
   
   
   // Invalid Lunks    
   aIl = $("ul.invalid-links li").find('span.ilText').clone().not(":last").append("|").end().text();
   
   // aIl = / www.atomicreach.coms | http:\/\/www.atomicreach.comsi\/ewruu /ig
   
   var linkArray = aIl.split('|');
   
   /*var regexIl = new RegExp(aIl,'gi');*/
 
   $("#highlight-il").toggle(function(){        
    
    /* 
     $('.preview').contents().highlightRegex(regexIl, {
      tagType:   'span',
      className: 'highlight-il',
      });  
     $('.preview').contents().find(".highlight-il").css("border-bottom", "2px solid orange");
     */
     
     
     $.each(linkArray, function( index, value ) {
       vlink = "[href='" + value + "']";
       $('.preview').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
     });
     
     
     $(this).text("Clear Underperforming Link");
   }, function(){
     // $(".preview").contents().find('body').find('style').remove(); 
     // $('.preview').contents().highlightRegex();
     // $('.preview').contents().find(".highlight-il").css("border-bottom", "");
     
   /*  $('.preview').contents().find(".highlight-il").removeAttr("style"); */
     
     $.each(linkArray, function( index, value ) {
       vlink = "[href='" + value + "']";
       $('.preview').contents().find(vlink).removeAttr("style");
     });
     
     $(this).text('Underperforming Link');
   })    
 


  $('#chkul').change(function() {
    
      if($(this).is(":checked")) {

         $.each(linkArray, function( index, value ) {
           vlink = "[href='" + value + "']";
           
           $('.preview').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
         });
         
               
      }else{
       
         $.each(linkArray, function( index, value ) {
           vlink = "[href='" + value + "']";
           $('.preview').contents().find(vlink).removeAttr("style");
         });
         
      }
  }); 

  // clear highlight before submiting form, this way will clean the html added to the iframe
  $('#node-form').submit(function(){
       $('.preview').contents().find(".highlight-so").contents().unwrap();
       $('.preview').contents().find(".highlight-sp").removeAttr("style");
       $('.preview').contents().highlightRegex(undefined, {
          tagType:   'span',
          className: 'highlight-sp',
        }); 
        
       $('.preview').contents().find(".highlight-grm").removeAttr("style"); 
       $('.preview').contents().highlightRegex(undefined, {
          tagType:   'span',
          className: 'highlight-grm',
        });   
        
       $.each(linkArray, function( index, value ) {
         vlink = "[href='" + value + "']";
         $('.preview').contents().find(vlink).removeAttr("style");
       });               
        
       return true;
   });    
    
});