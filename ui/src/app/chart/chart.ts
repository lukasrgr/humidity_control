import { QueryHistoricDataRequest } from './../../shared/request/QueryHistoricData';
import { Component } from "@angular/core";
import { Chart, LineController, LineElement, PointElement, LinearScale, Title, ChartItem, ChartType, ChartDataset, ChartOptions } from "chart.js"
import { differenceInMinutes, endOfDay, startOfDay } from 'date-fns';
import { AbstractData } from "src/shared/abstractData";
import { ReceiveDataResponse, Service } from "src/shared/service";


@Component({
    selector: 'chart',
    templateUrl: './chart.html'
})
export class ChartComponent extends AbstractData {
    private fromDate: Date;
    private toDate: Date;

    override ngOnInit(): void {
        this.toDate = endOfDay(new Date())
        this.fromDate = startOfDay(new Date());
        this.service.connectToWebsocket(new QueryHistoricDataRequest(this.fromDate, this.toDate)).then((chartData) => {
            this.chartData = chartData as ReceiveDataResponse;
        }).then(() => {
            this.createChart(this.chartData)
        })
    }

    createChart(chartData: ReceiveDataResponse) {

        let humidity = { name: "Feuchtigkeit", data: chartData.humidity, color: 'rgb(65,105,225)' };
        let temperature = { name: "Temperatur", data: chartData.temperature, color: 'rgb(178,34,34)' };
        let relay = { name: "Relay", data: chartData.relay, color: 'rgb(192,192,192)' };
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
                    },
                    legend: {
                        position: 'bottom'
                    }
                },
                scales: {
                    y: {
                        offset: true,
                        type: 'linear',
                        min: 0,
                        max: 100
                    },
                    y1: {
                        type: 'linear',
                        offset: true,
                        min: 0,
                        max: 1,
                        // display: true,
                        position: 'right',
                        grid: {
                            drawOnChartArea: false, // only want the grid lines for one axis to show up
                        },
                        // grid line settings

                    },
                },
                responsive: true,
            },
        })
        for (let dataset of [humidity, temperature, relay]) {
            chart.data.datasets.push({
                label: dataset.name,
                backgroundColor: dataset.color,
                borderColor: dataset.color,
                data: dataset.data,
                yAxisID: dataset.name == 'Relay' ? 'y1' : 'y',
                tension: 0.4
            })
        }
    }

    public getChartHeight(): number {
        return window.innerHeight / 1.8;
    }
}