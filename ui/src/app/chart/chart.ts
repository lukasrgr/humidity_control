import { Component } from "@angular/core";
import { Chart, ChartDataset, ChartItem } from "chart.js";
import { format } from 'date-fns';
import { ReceiveDataResponse, Service } from "src/shared/service";
import { QueryHistoricDataRequest } from './../../shared/request/QueryHistoricData';


@Component({
    selector: 'chart',
    templateUrl: './chart.html'
})
export class ChartComponent {

    public uniqueId = "test";
    public dataAccessible: boolean = false;

    private chart: Chart;
    private chartData: ReceiveDataResponse;

    constructor(private service: Service) { }

    ngOnInit(): void {
        let myChart = document.getElementById(this.uniqueId) as ChartItem;
        this.chart?.destroy()
        this.chart = new Chart(myChart, {
            data: {
                datasets: [],
                labels: [],
            },
            options: {
                elements: {
                    point: {
                        radius: 0
                    }
                },
                plugins: {
                    legend: {
                        position: 'bottom',
                    },
                    tooltip: { callbacks: {} }
                },
                scales: {
                    y: {
                        offset: true,
                    },
                    y2: {
                        offset: true,
                        position: 'right',
                        grid: {
                            drawOnChartArea: false, // only want the grid lines for one axis to show up
                        },
                    },
                },
                responsive: true,
            },
        })
        this.fetchChartData();
    }

    /**
     * Fetches Data from database
     */
    public fetchChartData() {
        this.service.connectToWebsocket(new QueryHistoricDataRequest(this.service.historyPeriod.fromDate, this.service.historyPeriod.toDate)).then((chartData) => {
            this.chartData = chartData as ReceiveDataResponse;
        }).then(() => {
            this.createChart(this.chartData)
        })
    }

    /**
     * Checks if at least one array in this response is not an empty array
     * 
     * @param chartData the chartData
     * @returns 
     */
    private isChartDataEmpty(chartData: ReceiveDataResponse): boolean {
        return Object.values(chartData).filter(element => (element as []).length > 0).length == 0
    }

    /**
     * Creates a chart with the passed data from an queryResponse
     * 
     * @param chartData the chartData
     */
    private createChart(chartData: ReceiveDataResponse) {

        let humidity = { name: "Feuchtigkeit", data: chartData.humidity, color: 'rgb(65,105,225)' };
        let temperature = { name: "Temperatur", data: chartData.temperature, color: 'rgb(178,34,34)' };

        let timestamps: string[] = [];
        let datasets: ChartDataset[] = [];

        // If response is empty show warning in message
        if (this.isChartDataEmpty(this.chartData)) {
            console.warn("no Data available for period from " +
                format(this.service.historyPeriod.fromDate, 'dd MMMM HH:mm') + ' - ' +
                format(this.service.historyPeriod.toDate, 'dd MMMM HH:mm'))

            datasets.push({
                type: 'line',
                label: "no Data available",
                data: [],
            })
        } else {

            chartData.timestamp.forEach(element => {
                timestamps.push(new Date(element).toLocaleString("default", { minute: "2-digit", hour: "2-digit" }));
            })
            for (let dataset of [humidity, temperature]) {
                let type: 'bar' | 'line' = dataset.name == 'Temperatur' ? 'line' : 'bar'
                let order: number = dataset.name == 'Temperatur' ? 1 : 2
                datasets.push({
                    type: type,
                    label: dataset.name,
                    backgroundColor: dataset.color,
                    borderColor: dataset.color,
                    data: dataset.data,
                    yAxisID: dataset.name == 'Relay' ? 'y1' : (dataset.name == 'Temperatur' ? 'y2' : 'y'),
                    order: order
                })
            }
        }

        this.chart.data.labels = timestamps;
        this.chart.data.datasets = datasets;

        // Trigger resizing to show fetched Data
        this.chart?.update()
    }

    public getChartHeight(): number {
        return window.innerHeight / 1.8;
    }
}