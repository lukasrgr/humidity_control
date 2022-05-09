import { Component, ElementRef, ViewChild } from "@angular/core";
import { Chart, ChartItem, ChartOptions, ChartDataset } from "chart.js";

@Component({
    selector: 'chart',
    templateUrl: './chart.html'
})
export class ChartComponent {

    public labels: Date[] = [];
    public datasets: ChartDataset[] = EMPTY_DATASET;
    public options: ChartOptions | null = null;
    public colors = []

    public myChart = document.getElementById("myChart") as ChartItem;

    // public barChart = new Chart(this.myChart, {
    //     type: 'bar',
    //     data: {
    //         labels: ["China", "India", "United States", "Indonesia", "Brazil", "Pakistan", "Nigeria", "Bangladesh", "Russia", "Japan"],
    //         datasets: [{
    //             label: 'Population',
    //             data: [1379302771, 1281935911, 326625791, 260580739, 207353391, 204924861, 190632261, 157826578, 142257519, 126451398],
    //             backgroundColor: [
    //                 'rgb(255, 99, 132)',
    //                 'rgb(54, 162, 235)',
    //                 'rgb(255, 206, 86)',
    //                 'rgb(75, 192, 192)',
    //                 'rgb(153, 102, 255)',
    //                 'rgb(255, 159, 64)',
    //                 'rgb(255, 99, 132)',
    //                 'rgb(54, 162, 235)',
    //                 'rgb(255, 206, 86)',
    //                 'rgb(75, 192, 192)',
    //                 'rgb(153, 102, 255)'
    //             ]
    //         }]
    //     }
    // });

    protected toBeRenamed() {

        let labels: Date[] = [];
        for (let timestamp of result.timestamps) {
            labels.push(new Date(timestamp));
        }
    }
}

export const EMPTY_DATASET = [{
    label: "no Data available",
    data: [],
    hidden: false
}];