$( //doc ready - whenever the doc is ready, execute this function
    function() {
        $('.hint').hide();
        $('h6').click //whenever an h6 is clicked, execute this function
            (
                function() {
                    $(this).next().fadeToggle(0); //slideToggle also
                }
            );
    }
)