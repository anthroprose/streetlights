function hexToRgb(hex) {
    // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
    var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
    hex = hex.replace(shorthandRegex, function(m, r, g, b) {
        return r + r + g + g + b + b;
    });

    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

function pushHexColors(hex) {
    
    color = hexToRgb(hex);
    
    $.ajax({
          url: '/colors/',
          dataType: 'json',
          data: {'r':color.r, 'g':color.g, 'b':color.b},
          success: function(data) {
            
          },
        });
    
}

function pushColors(r,g,b) {
    
    $.ajax({
          url: '/colors/',
          dataType: 'json',
          data: {'r':r, 'g':g, 'b':b},
          success: function(data) {
            
          },
        });
    
}

function pushColor(i,r,g,b) {
    
    $.ajax({
          url: '/color/',
          dataType: 'json',
          data: {'i':i, 'r':r, 'g':g, 'b':b},
          success: function(data) {
            
          },
        });
    
}