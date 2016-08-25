$(document).ready(function(){

/* Gère le hide/show du bouton "formulaire" de la page post.php */
$( ".toggle-visibility" ).click(function() {
  
  var target_selector = $(this).attr('data-target');
  var $target = $( target_selector );
  
  if ($target.is(':hidden'))
  {
    $target.show( "slow" );
  }
  else
  {
  	$target.hide( "slow" );
  }
  
  console.log($target.is(':visible'));  
});

/* Gère le hide/show du bouton "formulaire" de la page topic.php */
$( ".toggle-visibility2" ).hide;
$( ".toggle-visibility2" ).click(function() {
  
  var target_selector = $(this).attr('data-target');
  var $target = $( target_selector );
  
  if ($target.is(':hidden'))
  {
    $target.show( "slow" );
  }
  else
  {
  	$target.hide( "slow" );
  }
  
  console.log($target.is(':visible'));  
});

//Hover sur la pagination
     $('.pagination').hover(function() {
        $(this).addClass('transition');
   });
   
   
//Hover sur les menu bar

$(".hover").hover(function() {
    $(this).addClass("test");
}, function() {
    $(this).removeClass("test");
});
    
});
