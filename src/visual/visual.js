// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/06/26 14:46:10 by bwan-nan          #+#    #+#             //
//   Updated: 2019/07/02 18:26:52 by bwan-nan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var     cy;
var     data;
var     moves;
var     origins;
var     tunnels = [];
var     tunnel;
var     from;
var     antsColors = [];
var     ants = [];
var     k = 0;
var     antsOut = 0;
var     time;
var     pause = false;
var	  	colors = [];

$(document).ready(function() {
    $.getJSON("data.json", function(json) {
        data = json;
		cy = cytoscape({
			container: $("#cy"),
			elements: data,
			layout: {
			name: 'cose-bilkent',
			animate: false,
			randomize: true
			},
			style: [
				{
					selector: 'node',
					style: {
						'background-color': 'white',
						'label': 'data(id)',
                        'color': 'black'
					}
				},

				{
					selector: 'edge',
					style: {
						'width': 3,
						'line-color': 'white'
					}
				}
			],
		});
        cy.elements('node[flag = 0]').style('background-color', 'green');
        cy.elements('node[flag = 1]').style('background-color', 'red');
        moves = copyObject(Object.values(data.moves));
        origins = [cy.nodes('node[flag = 0]').id()];
        $("#ant_qty").text(data.ant_qty);
        $("#node_qty").text(data.nodes.length);
        $("#edge_qty").text(data.edges.length);
        $("#path_qty").text(data.paths.length);
        $("#rounds").text(k);
        $("#out").text(antsOut);
		document.getElementById("layoutButton").addEventListener("click", function(){
            var layout = cy.layout({
                name: 'cose-bilkent',
          		animate: 'end',
				animationEasing: 'ease-out',
           	    animationDuration: 1000,
				randomize: true
         	});
          	layout.run();
        });
		document.getElementById("randomize").addEventListener("click", function(){
			var layout = cy.layout({
				name: 'random',
				animate: true,
				animationDuration: 1000,
				animationEasing: 'ease-out'
			});
		    layout.run();
		});

        data.paths.forEach(function(p) {
          var color = getRandomColor();
          colors.push({'path': p.path, 'color': color});
        });
        getAntsColors();

        cy.nodes('node[flag = 1]').style('border-width', '1px');
        cy.nodes('node[flag = 0]').style('border-width', '1px');
        var width = cy.nodes('node[flag = 1]').style().width;
        var new_width = width.substr(0, width.length-2) * 1.5 + 'px';
        cy.nodes('node[flag = 0]').style('width', new_width);
        cy.nodes('node[flag = 0]').style('height', new_width);
        cy.nodes('node[flag = 1]').style('width', new_width);
        cy.nodes('node[flag = 1]').style('height', new_width);

        $("#reset").click(function() {
            k = 0;
            antsOut = 0;
            origins = [cy.nodes('node[flag = 0]').id()];
            $("#rounds").text(k);
            $("#out").text(antsOut);
            moves = copyObject(Object.values(data.moves));
            cy.elements('node').forEach(function(node) {
                if (node.id() != cy.nodes('node[flag = 1]').id()
                && node.id() != cy.nodes('node[flag = 0]').id()) {
                    cy.nodes('node[id = "' + node.id() + '"]').style('background-color', 'white');
                    cy.nodes('node[id = "' + node.id() + '"]').style('opacity', 1.0);
                }
            });
            cy.edges().forEach(function(edge) {
                edge.style('line-color', 'white');
            });
        });

        $("#print_paths").click(function() {
            colors = [];
            ants = [];
            data.paths.forEach(function(p) {
                print_path(p.path);
            });
            getAntsColors();
        });

        function        print_path(path) {
            var color = getRandomColor();
			      colors.push({'path': path, 'color': color});
            var j;
            for (j = 0; j < path.length; j++)  {
                if (path[j] != cy.nodes('node[flag = 1]').id()
                && path[j] != cy.nodes('node[flag = 0]').id()) {
                room = path[j];
                    cy.nodes('node[id = "' + path[j] + '"]').style('background-color', color[0]);
                }
                tunnel = cy.edges().filter(function(edge) {
                    var e1 = (edge.source().id() == path[j] && edge.target().id() == path[j + 1]);
                    var e2 = (edge.source().id() == path[j + 1] && edge.target().id() == path[j]);
                    return e1 || e2;
                });
                tunnel.style('line-color', color[0]);
            }
        }

        function        getRandomColor() {
            var tmp;
            var colors = [];

            colors[0] = 'rgb(';
            colors[1] = 'rgb(';
            for (var i = 0; i < 3; i++) {
                tmp = Math.floor(Math.random() * 220);
                colors[0] += tmp;
                colors[1] += tmp + 30;
				        if (i != 2) {
					           colors[0] += ', ';
                     colors[1] += ', ';
                } else {
					           colors[0] += ')';
                     colors[1] += ')';
                }
            }
            return colors;
        }


		function		getOpacity(number) {
			if (number % 2)
				return 0.7;
			return 1.0;
		}

    function  getColor(room, k) {
      var   rightColor;
      var   i;

      colors.forEach(function(elem) {
        if (elem.path.includes(room)) {
          if (k % 2)
            rightColor = elem.color[0];
          else {
            rightColor = elem.color[1];
          }
        }
      });
      return rightColor;
    }

    function        getAntsColors() {
      var   k = 0;
      var   exists;

      data.moves.forEach(function(round) {
        round.forEach(function(move){
            exists = false;
            ants.forEach(function(ant) {
              if (ant.ant_id == move.ant_id) {
                exists = true;
              }
            });
            if (exists == false) {
              ants.push({'ant_id': move.ant_id, 'color': getColor(move.dest, k), 'opacity': getOpacity(k)});
            }
        });
        k += 1;
      });
    }

        function        getCorrespondingColor(ant_id) {
          var color_and_opacity;

          ants.forEach(function(ant) {
            if (ant.ant_id == ant_id) {
              color_and_opacity = [ant.color, ant.opacity];
            }
          });
          return color_and_opacity;
        }

        $("#next").click(function() {
            if (k < data.rounds) {
                var points = moves[k];
                origins.forEach(function(origin) {
                    if (origin.dest != cy.nodes('node[flag = 0]').id()
                    && origin.dest != cy.nodes('node[flag = 1]').id()) {
                        cy.elements('node[id = "' + origin.dest + '"]')
                            .style('background-color', 'white');
                        cy.elements('node[id = "' + origin.dest + '"]')
                            .style('opacity', 1.0);

                 }
                });
                tunnels.forEach(function(tunnel) {
                    if (tunnel.style() && tunnel.style().lineColor != 'white')
                        tunnel.style('line-color', 'white');
                });
                points.forEach(function(point) {
                      var tab = getCorrespondingColor(point.ant_id);
                      if (point.dest != cy.nodes('node[flag = 1]').id()) {
                        cy.nodes('node[id = "' + point.dest + '"]')
                            .style('background-color', tab[0]);
                        cy.nodes('node[id = "' + point.dest + '"]')
                            .style('opacity', 1.0);
                      }
                        var from_name = getParentName(point.dest, point.ant_id);
                        from = cy.nodes('node[id = "' + from_name + '"]');
                        tunnel = cy.edges().filter(function(elem) {
                            var e1 = (from.id() == elem.source().id() && elem.target().id() == point.dest);
                            var e2 = (elem.source().id() == point.dest && from.id() == elem.target().id());
                            return e1 || e2;
                        });
                        tunnel.style('line-color', tab[0]);
                        tunnels.push(tunnel);
                  if (point.dest == cy.nodes('node[flag = 1]').id()) {
                      antsOut++;
                  }
                     for (var node of data.nodes) {
                        if (node.data.id == point.dest) {
                            node.data.ant_id = point.ant_id;
                            break ;
                        }
                    }

                });
                origins = points;
                k += 1;
                $("#rounds").text(k);
                $("#out").text(antsOut);
            } else {
                cy.edges().forEach(function(edge) {
                    edge.style('line-color', 'white');
                });
            }
        });

        function        getParentName(dest, ant_id) {
          var name;
          var i;

          if (dest == cy.nodes('node[flag = 1]').id()) {
              name = getParentMatchingAntId(ant_id);
          } else {
            data.paths.forEach(function(elem){
              for (i = 0; i < elem.path.length; i++) {
                if (elem.path[i] == dest)
                  name = elem.path[i - 1];
              }
            });
          }
          return name;
        }

        function        getParentMatchingAntId(ant_id) {
            var matching_name;
            data.nodes.forEach(function(node) {
                if (node.data.ant_id == ant_id) {
                    matching_name = node.data.id;
                }
            });
            return (matching_name);
        }


        $("#play").click(function() {
            pause = false;
            play_button();
          });

        function        play_button() {
            var timeOut;
            if (data.moves.length > 50)
                timeOut = 10;
            else if (data.moves.length > 20)
                timeOut = 200;
            else
                timeOut = 500;
            if (antsOut != data.ant_qty && pause == false) {
                setTimeout(function() {
                    $("#next").trigger("click");
                    play_button();
                }, timeOut);
            } else {
                cy.edges().forEach(function(edge) {
                    edge.style('line-color', 'white');
                });
            }
        }

        $("#pause").click(function() {
            pause = true;
        });
	});
});

function            copyObject(src) {
    return Object.assign({}, src);
}
