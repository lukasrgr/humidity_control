import { Component } from "@angular/core";
import { Chart, LineController, LineElement, PointElement, LinearScale, Title, ChartItem, ChartType, ChartDataset, ChartOptions } from "chart.js"
import { AbstractData } from "src/shared/abstractData";
import { ReceiveDataResponse, Service } from "src/shared/service";


@Component({
    selector: 'chart',
    templateUrl: './chart.html'
})
export class ChartComponent extends AbstractData {

    override ngOnInit(): void {
        this.service.connectToWebsocket({ method: "receiveData" }).then((chartData) => {
            this.chartData = chartData as ReceiveDataResponse;
        }).finally(() => {
            this.createChart(this.chartData)
        })
    }

    createChart(chartData: ReceiveDataResponse) {

        let humidity = { name: "Feuchtigkeit", data: chartData.humidity, color: 'rgb(0,0,255)' };
        let temperature = { name: "Temperatur", data: chartData.temperature, color: 'rgb(255,0,0)' };
        let relay = { name: "Relay", data: chartData.relay, color: 'rgb(0,255,0)' };
        let timestamps: string[] = [];

        chartData.timestamp.forEach(element => {
            timestamps.push(new Date(element).toLocaleString("default", { minute: "2-digit", hour: "2-digit" }));
        })

        let myChart = document.getElementById("myChart") as ChartItem;
        const chart = new Chart(myChart, {
            type: 'line',
            data: {
                datasets: [],
                labels: timestamps,
            },
            options: {
                plugins: {
                    title: {
                        display: true,
                    }
                },
                scales: {
                    y: {
                        offset: true,
                        type: 'linear',
                        min: 0,
                        max: 100
                    }
                },
                responsive: true
            },
        })
        for (let dataset of [humidity, temperature, relay]) {
            chart.data.datasets.push({
                label: dataset.name,
                backgroundColor: dataset.color,
                borderColor: dataset.color,
                data: dataset.data,
            })
        }
    }

    public getChartHeight(): number {
        return window.innerHeight / 1.8;
    }
}