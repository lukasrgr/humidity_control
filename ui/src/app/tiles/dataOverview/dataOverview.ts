import { Component } from "@angular/core";
import { Chart, LineController, LineElement, PointElement, LinearScale, Title, ChartItem, ChartType, ChartDataset, ChartOptions } from "chart.js";
import { AbstractData } from "src/shared/abstractData";

@Component({
    selector: "dataOverview",
    templateUrl: "./dataOverview.html"
})
export class DataOverviewTile extends AbstractData {
    public data = {
        labels: [
            'Red',
            'Blue',
            'Yellow'
        ],
        datasets: [{
            label: 'My First Dataset',
            data: [300, 50, 100],
            backgroundColor: [
                'rgb(255, 99, 132)',
                'rgb(54, 162, 235)',
                'rgb(255, 205, 86)'
            ],
            hoverOffset: 4
        }]
    };
    public config = {
        type: 'line',
        data: this.data,
        options: {}
    };

    createChart() {
        let temperatureChart = document.getElementById("temperature") as ChartItem;
        let chart = new Chart(temperatureChart, {
            type: 'pie',
            data: {
                datasets: [{
                    data: [50],
                    label: "Temperature",
                    backgroundColor: [
                        'rgb(247, 70, 74)'],
                }],
                labels: [],
            },
            options: {
                cutout: "70%",
                radius: "50%",
                // datasets: {
                //     doughnut: {
                //      tot   
                //     }
                // },
                // radius: "40%",
                plugins: {
                    title: {
                        display: true,
                    }
                },

                scales: {

                    y: {
                        //         offset: true,
                        //         type: 'linear',
                        //         min: 0,
                        max: 100,
                        display: false
                    },
                    x: {
                        ticks: {

                        },
                        max: 100,
                        display: false
                    }
                },
                responsive: true
            },

        });
    }
}